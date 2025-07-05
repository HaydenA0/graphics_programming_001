#include "glad/glad.h" // should be on top
#include <GLFW/glfw3.h>
#include <iostream>
#define WIDTH 400
#define HEIGHT 300
const char *VERTEXSHADERSOURCE =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *FRAGMENTSHADERSOURCE =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

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
  // let's use it now

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

  // let's now use GL functions that we can use now
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // I want to use VBO as the current GL_ARRAY_BUFFER for vertex storage
  // Let's actually send it

  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
  // GL_STATIC_DRAW means Data won’t change, used many times : const int* data
  // almost

  // VERTEX SHADER SETUP
  unsigned int VERTEXSHADER; // create ID since it's an OpenGL Object
  VERTEXSHADER =
      glCreateShader(GL_VERTEX_SHADER); // associate the ID with a VERTEXSHADER
  glShaderSource(VERTEXSHADER, 1, &VERTEXSHADERSOURCE, NULL);
  glCompileShader(VERTEXSHADER);
  // compiling the shader
  // for some debugging

  int success_vertex;            // obvious
  char vertex_compiler_log[512]; // string for the compilationg
  glGetShaderiv(VERTEXSHADER, GL_COMPILE_STATUS,
                &success_vertex); // ask for the logs
  if (!success_vertex) {
    glGetShaderInfoLog(
        VERTEXSHADER, 512, NULL,
        vertex_compiler_log); // get the logs if error was to happen
    std::cout << "ERROR :: COMPILING SHADERS FAILED\n"
              << vertex_compiler_log << "\n";
    // print logs
  }

  // FRAGMENT SHADER SETUP
  // same steps as in the VERTEXSHADER

  unsigned int FRAGMENTSHADER;
  FRAGMENTSHADER = glad_glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FRAGMENTSHADER, 1, &FRAGMENTSHADERSOURCE, NULL);
  glCompileShader(FRAGMENTSHADER);
  // debugging

  int success_fragment;
  char fragment_compiler_log[512]; // string for the compilationg
  glGetShaderiv(VERTEXSHADER, GL_COMPILE_STATUS,
                &success_fragment); // ask for the logs
  if (!success_fragment) {
    glGetShaderInfoLog(
        VERTEXSHADER, 512, NULL,
        fragment_compiler_log); // get the logs if error was to happen
    std::cout << "ERROR :: COMPILING SHADERS FAILED\n"
              << fragment_compiler_log << "\n";
    // print logs
  }

  // creating shader program to link vertex and fragment shaders
  // it takes the input of the VS and give it to the FS

  unsigned int SHADER_PROGRAM; // ID
  SHADER_PROGRAM = glCreateProgram();

  glAttachShader(SHADER_PROGRAM, VERTEXSHADER);
  glAttachShader(SHADER_PROGRAM, FRAGMENTSHADER);
  glLinkProgram(SHADER_PROGRAM);

  // again debugging

  int success_linker;
  char linker_compiler_log[512]; // string for the compilationg
  glGetShaderiv(VERTEXSHADER, GL_COMPILE_STATUS,
                &success_linker); // ask for the logs
  if (!success_linker) {
    glGetShaderInfoLog(
        VERTEXSHADER, 512, NULL,
        linker_compiler_log); // get the logs if error was to happen
    std::cout << "ERROR :: COMPILING SHADERS FAILED\n"
              << linker_compiler_log << "\n";
    // print logs
  }

  // Make this specific, compiled set of vertex and fragment shaders
  // the active one. All drawing commands that follow should be
  // processed using this program = Vertex + Fragment
  glDeleteShader(VERTEXSHADER);
  glDeleteShader(FRAGMENTSHADER);
  // cleaning the shaders

  // defining an VAO

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  // Linking vertex attributes

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  // 0 = which of the VertexAttribute we are setting in, since we used layout
  // location 0 and this is the first one we will set it to 0 3 is the number of
  // the number of components of the attribute (x position the data type we are
  // working with is floats so it is what we are going with the normalization is
  // not in our interest for now so we will be going for False an attribute ends
  // at [float],[float],[float] so 3 x float
  glEnableVertexAttribArray(0);

  // set up is ready and now we can link everything
  glUseProgram(SHADER_PROGRAM);

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

    glUseProgram(SHADER_PROGRAM);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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
