#pragma once
#include "main.h"

struct Camera {
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;   
};

Camera * createCamera();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);