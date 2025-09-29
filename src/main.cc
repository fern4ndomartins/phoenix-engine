#include "../include/main.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    GLFWwindow* window = create_window(SCR_WIDTH, SCR_HEIGHT);
    if (!window) {
        std::cout << "failed to create window.";
        return -1;
    }

    Shader shader = Shader("../assets/shaders/shader3d.vs", "../assets/shaders/shader3d.fs");
    Shader shaderBlack = Shader("../assets/shaders/shader3d.vs", "../assets/shaders/shader3d-black.fs");

    float vertices[] = {         //texture stuff ;;;;;;
         0.0f, 0.5f, 0.0f,    0.0f, 0.0f,
         0.5f, 0.0f, 0.0f,    1.0f, 0.0f,
        -0.5f, 0.0f, 0.0f,    0.5f, 1.0f

    };

    float cubeVertices[] = {
        // positions          
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
    
    float smallCubeVertices[] = {
        // positions (size = 0.5, center_x = 0.75)
        0.50f, -0.25f, -0.25f,
        1.00f, -0.25f, -0.25f,
        1.00f,  0.25f, -0.25f,
        1.00f,  0.25f, -0.25f,
        0.50f,  0.25f, -0.25f,
        0.50f, -0.25f, -0.25f,

        0.50f, -0.25f,  0.25f,
        1.00f, -0.25f,  0.25f,
        1.00f,  0.25f,  0.25f,
        1.00f,  0.25f,  0.25f,
        0.50f,  0.25f,  0.25f,
        0.50f, -0.25f,  0.25f,

        0.50f,  0.25f,  0.25f,
        0.50f,  0.25f, -0.25f,
        0.50f, -0.25f, -0.25f,
        0.50f, -0.25f, -0.25f,
        0.50f, -0.25f,  0.25f,
        0.50f,  0.25f,  0.25f,

        1.00f,  0.25f,  0.25f,
        1.00f,  0.25f, -0.25f,
        1.00f, -0.25f, -0.25f,
        1.00f, -0.25f, -0.25f,
        1.00f, -0.25f,  0.25f,
        1.00f,  0.25f,  0.25f,

        0.50f, -0.25f, -0.25f,
        1.00f, -0.25f, -0.25f,
        1.00f, -0.25f,  0.25f,
        1.00f, -0.25f,  0.25f,
        0.50f, -0.25f,  0.25f,
        0.50f, -0.25f, -0.25f,

        0.50f,  0.25f, -0.25f,
        1.00f,  0.25f, -0.25f,
        1.00f,  0.25f,  0.25f,
        1.00f,  0.25f,  0.25f,
        0.50f,  0.25f,  0.25f,
        0.50f,  0.25f, -0.25f
    };

    
    float texCoords[] = {
        0.0f, 0.0f,   
        1.0f, 0.0f,  
        0.5f, 1.0f   
    };

    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); 
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../src/wall.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    unsigned int VBO, VBO1, VAO, VAO1;
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(smallCubeVertices), smallCubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    struct Camera *cam = new Camera;
    cam->cameraFront = cameraFront;
    cam->cameraPos = cameraPos;
    cam->cameraUp = cameraUp;


    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window, cam);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(),  glm::vec3(0.5f, 1.0f, 0.0f)); 
        glm::mat4 view = glm::lookAt(cam->cameraPos, cam->cameraPos + cam->cameraFront, cam->cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 mvp = projection * view * model;

        glBindVertexArray(VAO1);

        unsigned int mvpLoc = glGetUniformLocation(shader.ID, "MVP");

        shader.use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        shaderBlack.use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.0f);

        unsigned int mvpLocBlack = glGetUniformLocation(shaderBlack.ID, "MVP");
        glUniformMatrix4fv(mvpLocBlack, 1, GL_FALSE, glm::value_ptr(mvp));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glBindVertexArray(VAO);
        shader.use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


