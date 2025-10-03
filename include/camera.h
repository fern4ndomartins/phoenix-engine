#pragma once
#include "main.h"
#include <GLFW/glfw3.h>

struct Collider {
    glm::vec3 min;  
    glm::vec3 max;  
};

bool checkCollision(glm::vec3 camPos, float radius, Collider box);

struct Camera {
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;  
     
};

Camera * createCamera(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);