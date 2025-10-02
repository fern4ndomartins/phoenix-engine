#pragma once 
#include "main.h"

class Entity {
private:
    glm::vec3 rotation;  
    glm::vec3 scale;
    
public:
    glm::vec3 colorRGB;
    glm::vec3 position;
    Entity(glm::vec3, std::string);
};