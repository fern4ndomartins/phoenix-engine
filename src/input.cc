#include "../include/input.h"

void processInput(GLFWwindow *window, struct Camera *cam)
{
    float cameraSpeed = 0.05f; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->cameraPos += cameraSpeed * cam->cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->cameraPos -= cameraSpeed * cam->cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->cameraPos -= glm::normalize(glm::cross(cam->cameraFront, cam->cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->cameraPos += glm::normalize(glm::cross(cam->cameraFront, cam->cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam->cameraPos += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);  
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam->cameraPos -= cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);  

    

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
