#include "../include/entity.h"


Entity::Entity(glm::vec3 pos, std::string color) 
        : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f) 
{
    position = pos;    
    // make this a switch case later !!!!
    if (color == "red") {
        colorRGB = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    if (color == "yellow") {
        colorRGB = glm::vec3(1.0f, 1.0f, 0.0f);
    }
    if (color=="blue"){
        colorRGB = glm::vec3(0.0f, 0.0f, 1.0f);
    }
    if (color=="green"){
        colorRGB = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    if (color=="white"){
        colorRGB = glm::vec3(1.0f, 1.0f, 1.0f);
    }
}
        
