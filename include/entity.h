#pragma once 
#include "main.h"
#include <glm/fwd.hpp>

class Entity {
public:
    Entity* player_;
    glm::vec3 rotation;  
    glm::vec3 scale;
    glm::vec3 colorRGB;
    glm::vec3 position;
    Entity(glm::vec3, std::string, float scale, Entity* player);
    glm::vec3 getMax(); 
    glm::vec3 getMin(); 
    bool checkCollision(Entity *other); 

};