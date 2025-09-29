#include "../include/input.h"

void processInput(GLFWwindow *window, float *xcoord, float *ycoord)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        *ycoord+=0.01f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        *ycoord-=0.01f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        *xcoord+=0.01f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        *xcoord-=0.01f;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
