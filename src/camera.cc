#include "../include/camera.h"

float lastX = 400, lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;
Camera* cam;  

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= 0.1f;  // Sensitivity
    yoffset *= 0.1f;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Update cameraFront
    cam->cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cam->cameraFront.y = sin(glm::radians(pitch));
    cam->cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cam->cameraFront = glm::normalize(cam->cameraFront);
}

Camera * createCamera(GLFWwindow *window) {
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    struct Camera *cam = new Camera;
    cam->cameraFront = cameraFront;
    cam->cameraPos = cameraPos;
    cam->cameraUp = cameraUp;
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    ::cam = cam;
    return cam;
}