#pragma once
#include "main.h"
#include <GLFW/glfw3.h>

struct Camera {
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;   
};

Camera * createCamera(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);