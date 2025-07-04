#include "glad/glad.h" // should be on top
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#define WIDTH 400
#define HEIGHT 300

void frame_buffer_resize_callback(GLFWwindow *window, int width, int height) {
  glad_glViewport(0, 0, width, height);
}
//   When you resize a window:
//   The operating system changes the size of the window.
//   GLFW notices the change and tells you.
//   OpenGL does not automatically adjust — so you must manually update its
//  drawing area using glViewport.
//  we didn’t ask for a new window that is why we dont need to call a new one

void handle_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK)) {
    glfwSetWindowShouldClose(window, true);
  }
  // here we closing with the escape
  // handle the input of the OS
}

int main() {

  float triangle[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                      0.0f,  0.0f,  0.5f, 0.0f}; // x,y,z,  x,y,z,  x,y,z
  // instead of sending vertices from the cpu to the gpu each fraim
  // we can gather them all into one big buffer and send it to the
  // GPU, it's called VBO vertex buffer object, OpenGL object

  unsigned int *VBO;
  glGenBuffers(1, VBO);
  // stopped here

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // I want opengl 3.x
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // I want opengl .3 = 3.3
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // I want to choose a profile that is the core version
  // the core version is the version without the old stuff,
  // only the new stuff
  // GLFW_OPENGL_COMPAT_PROFILE would be for new and old opengl

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Demo01", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to start the window\n";
    return -1;
  }
  glfwMakeContextCurrent(window);
  // create the window context,
  // context is the tools we will be using
  // GLFW is responsible for:
  // Creating windows
  // Handling input (keyboard, mouse, etc.)
  // Managing OpenGL context
  // Making your code OS-independent for those tasks
  // GLAD is responsible for:
  // Loading actual OpenGL functions from your system’s graphics driver
  // Handling which version of OpenGL you want
  // Making those functions usable in your code (like glGenBuffers,
  // glDrawArrays, etc.)

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed loading GLAD\n";
    return -1;
  }
  glad_glViewport(0, 0, WIDTH, HEIGHT);
  // Behind the scenes OpenGL uses the data specified via glViewport to
  // transform the 2D coordinates it processed to coordinates on your screen.
  // For example, a processed point of location (-0.5,0.5) would (as its final
  // transformation) be mapped to (200,450) in screen coordinates. Note that
  // processed coordinates in OpenGL are between -1 and 1 so we effectively map
  // from the range (-1 to 1) to (0, 800) and (0, 600).

  glfwSetFramebufferSizeCallback(window, frame_buffer_resize_callback);

  while (!glfwWindowShouldClose(window)) {
    // if the os is requesting to close the window
    handle_input(window);
    // You want to know what the user did (pressed keys, moved mouse)
    // before you decide what to draw

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // Sets the color you want the screen to be filled with when you
    // clear it.
    // In this case, a greenish-blue (not pure green).
    glClear(GL_COLOR_BUFFER_BIT);
    // clear it and make the color actually greenish
    // In OpenGL, a state is a setting that OpenGL remembers internally.
    // Think of OpenGL like a painter who keeps a notepad:
    // You tell them: "Next time you paint, use blue."
    // They write that down (set the state).
    // Later, when they start painting,
    // they look at the notepad(use the state).glfwSwapBuffers(window);
    glfwSwapBuffers(window);
    // swap front buffer with back front
    // will swap the color buffer
    // (a large 2D buffer that contains color values for each
    // pixel in GLFW’s window)
    // after rendering so that you don't want to show the frame before it's
    // done.
    glfwPollEvents();
    // check for inputs from the devices
    // updates the window state,
    // and calls the corresponding functions
    // If you poll before rendering, you'll be using "last frame’s" events — not
    // ideal.
  }

  glfwTerminate();
  return 0;
}
