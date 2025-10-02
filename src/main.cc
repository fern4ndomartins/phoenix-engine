#include "../include/main.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

int main()
{
    GLFWwindow* window = create_window(SCR_WIDTH, SCR_HEIGHT);
    if (!window) {
        std::cout << "failed to create window.";
        return -1;
    }
    initStats(window);   

    Shader shader = Shader("../assets/shaders/shader3d.vs", "../assets/shaders/shader3d.fs");
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cubeVerticesSize, cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Camera *cam = createCamera(window);

    std::vector<Entity*> objects;
    Entity *obj1 = new Entity(glm::vec3(1.0f, 0.5f, 5.0f), "white");  
    Entity *obj2 = new Entity(glm::vec3(5.0f, 0.0f, 5.0f), "yellow");  
    Entity *obj3 = new Entity(glm::vec3(7.0f, 0.0f, 5.0f), "green");  
    objects.push_back(obj1);
    objects.push_back(obj2);
    objects.push_back(obj3);
    
    shader.use();

    unsigned int mvpLoc = glGetUniformLocation(shader.ID, "MVP");
    unsigned int colorLoc = glGetUniformLocation(shader.ID, "color");

    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window, cam);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0.0f,  glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(10.0f, 1.0f, 1.0f));
        glm::mat4 view = glm::lookAt(cam->cameraPos, cam->cameraPos + cam->cameraFront, cam->cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 mvp = projection * view * model;        

        for (auto& obj : objects) {
            model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(),  obj->position);
            model = glm::translate(model, obj->position);
            mvp = projection * view * model;
            glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
            glUniform3f(colorLoc, obj->colorRGB.x, obj->colorRGB.y, obj->colorRGB.z);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            
        }

        renderStats();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


