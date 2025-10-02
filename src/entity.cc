#include "../include/entity.h"
#include <glm/fwd.hpp>


Entity::Entity(glm::vec3 pos, std::string color, float scale, Entity* player) 
        : position(pos), rotation( 0.0f), scale(scale), player_(player) 
{
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
        
glm::vec3 Entity::getMin()  {
    return position - (scale * 0.5f);
}
    
glm::vec3 Entity::getMax()  {
    return position + (scale * 0.5f);
}

bool Entity::checkCollision(Entity *other) {
    glm::vec3 aMin = getMin();
    glm::vec3 aMax = getMax();
    glm::vec3 bMin = other->getMin();
    glm::vec3 bMax = other->getMax();
    
    return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
            (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
            (aMin.z <= bMax.z && aMax.z >= bMin.z);
    
}