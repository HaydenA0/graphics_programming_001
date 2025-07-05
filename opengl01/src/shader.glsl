#version 330 core 
// to match 3.3 of OpenGL
// again core here means we are using only 
// the new functionalities of GLSL


layout (location = 0 ) in vec3 aPos;

void main () { // RUN FOR EVERY VERTEX
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);  
    //gl_Position is a built-in GLSL variable that stores the 
    //final position of the vertex in clip space.
    //The w value is needed for perspective division, 
    //which helps convert 3D coordinates to 2D screen space.
    // we are adding it at the end with value 1, because in the 
    // app, the vertices coordinates are already in [-1,1]
}
