#include "../include/main.h"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

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
    glBufferData(GL_ARRAY_BUFFER, cubeVerticesWtTextureSize, cubeVerticesWtTexture, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load("../assets/tiles.jpeg", &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        std::cout << "Texture loaded: " << width << "x" << height << ", channels: " << nrChannels << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    Camera *cam = createCamera(window);

    Entity *player = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), "red", 0.0f, NULL); 

    std::vector<Entity*> objects;
    Entity *obj1 = new Entity(glm::vec3(1.0f, 0.5f, 5.0f), "white", 1.0f, player);  
    Entity *obj2 = new Entity(glm::vec3(5.0f, 0.0f, 5.0f), "yellow", 1.0f, player);  
    Entity *obj3 = new Entity(glm::vec3(7.0f, 0.0f, 5.0f), "green", 1.0f, player);  
    objects.push_back(obj1);
    objects.push_back(obj2);
    objects.push_back(obj3);

    shader.use();
    unsigned int textureLoc = glGetUniformLocation(shader.ID, "texture1");
    glUniform1i(textureLoc, 0);
    
    unsigned int mvpLoc = glGetUniformLocation(shader.ID, "MVP");
    unsigned int colorLoc = glGetUniformLocation(shader.ID, "color");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

        shader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        player->position = cam->cameraPos;

        std::sort(objects.begin(), objects.end(), [cam](const Entity* a, const Entity* b) {
            float distA = glm::distance(a->position, cam->cameraPos);
            float distB = glm::distance(b->position, cam->cameraPos);
            return distA > distB;  
        });


        glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0.0f,  glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(10.0f, 1.0f, 1.0f));
        glm::mat4 view = glm::lookAt(cam->cameraPos, cam->cameraPos + cam->cameraFront, cam->cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 mvp = projection * view * model;        

        for (auto& obj : objects) {
            model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(),  obj->position);
            model = glm::translate(model, obj->position);
            model = glm::scale(model, obj->scale);
            mvp = projection * view * model;
            glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
            glUniform3f(colorLoc, obj->colorRGB.x, obj->colorRGB.y, obj->colorRGB.z);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            
        }


        for (int i = 0; i < objects.size(); i++) {
        for (int j = i + 1; j < objects.size(); j++) {
            if (objects[i]->checkCollision(objects[j])) {
                std::cout << "Collision between object " << i << " and " << j << std::endl;
            }
        }
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


