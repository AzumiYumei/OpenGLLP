

#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Camera.h"
#include"Shader.h"
#include"Texture.h"
#include"Light.h"
#include"Material.h"
using namespace std;

#include<iostream>
#include<string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int screenWeight = 600;
int screenHeight = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool isFirstOpen = true;

float lastX = screenWeight / 2.0f;
float lastY = screenHeight / 2.0f;

//��������
//float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//};

//�����뷨������
float vertices[] = {
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

//���������
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.5f, 0.05f, 3.0f, -80.0f, 80.0f,45.0f);
//��λ֡ʱ���
float DeletaTime()
{
    deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();
    return deltaTime;
}
//��������
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, DeletaTime());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, DeletaTime());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, DeletaTime());
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, DeletaTime());
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(SPACE, DeletaTime()); 
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(CONTROL, DeletaTime());
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(SHIFT, DeletaTime());
    else 
        camera.ProcessKeyboard(NONE, DeletaTime());

}
//�������
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = xposIn;
    float ypos = yposIn;

    if (isFirstOpen)
    {
        lastX = xpos;
        lastY = ypos;
        isFirstOpen = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
//��������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
//��ѭ����Ⱦ��
void LoopRanden(Shader shader,unsigned int VAO,float near,float far)
{
    shader.use();

    shader.OpenProjection(camera, screenWeight, screenHeight, near, far);

    shader.OpenView(camera);

    //��ʼ��Ⱦ
    glBindVertexArray(VAO);
}

void main()
{
#pragma region WindowCrate&Init



    //��ʼ��
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    //��������
    GLFWwindow* window = glfwCreateWindow(screenWeight, screenHeight, "LearnOpenGL", NULL, NULL);

    glViewport(0, 0, screenWeight, screenHeight);

    //�������������������ʽ����ô���ڴ����ͻ����
    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        printf("Error\n");

#pragma endregion

    //���������Ϣ
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //����Ȳ���
    glEnable(GL_DEPTH_TEST);
#pragma region VAO&VBO&EBOBind

    //����VAO��VBO��EBO������VAO
    unsigned int VAO, VBO, EBO, lightVAO ,cubeVAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //�󶨶������
    glBindVertexArray(VAO);
    //�󶨶��㻺�����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //���������鴢�浽���㻺����
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    ////���ö���ָ��
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);


    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
   

#pragma endregion

    //����shader
    Shader shader("vertex.txt", "fragment.txt");
    Shader lightShader("lightVertex.txt", "lightFragment.txt");//����shader
    Shader cubeShader("cubeVertex.txt","cubeFragment.txt");//���ⷽ��shader

    //��ת����
    stbi_set_flip_vertically_on_load(true);

    //������ͼ
    Texture texture1("wall.jpg",3,"GL_REPEAT","GL_REPEAT","GL_NEAREST","GL_NEAREST");
    Texture texture2( "awesomeface.png", 4, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    
    //����ͼ���ݽ�fragment��uniform��
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        //������󶨵�����Ԫ��ʹ������Ԫ�Ͳ��ش���uniformҲ��ʹ��
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1.textureID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2.textureID);

        //LoopRanden(shader, VAO, 0.1f, 100.0f);
        //for (int i = 0; i < 10; i++)
        //{
        //    glm::mat4 model = glm::mat4(1.0f);
        //    model = glm::translate(model, cubePositions[i]);
        //    float angle = 20.0f * i;
        //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //    //shader.setMat4("model", model);
        //    shader.setMat4("model", model);
        //    //���ƺ���
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}


        lightShader.use();
        lightShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        lightShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
       
        lightShader.setVec3("cameraPos", camera.cameraPosition);
        lightShader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
        lightShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
        lightShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        lightShader.setFloat("material.shininess", 32.0f);

        lightShader.setVec3("light.position", glm::vec3(cubePositions[1].x * sin(glfwGetTime()) / 2 + 0.5,
            cubePositions[1].y * cos(glfwGetTime()) / 2 + 0.5,
            cubePositions[1].z));
        lightShader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        lightShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); 
        lightShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));


        LoopRanden(lightShader, lightVAO, 0.1f, 100.0f);
        for (int i = 2; i < 5; i++)
        {
             glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
            lightShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        LoopRanden(cubeShader, cubeVAO, 0.1f, 100.0f);
        glm::mat4 model1 = glm::mat4(1.0f);
        model1 = glm::translate(model1, glm::vec3(cubePositions[1].x * sin(glfwGetTime()) / 2 + 0.5,
            cubePositions[1].y * cos(glfwGetTime()) / 2 + 0.5,
            cubePositions[1].z));
        cubeShader.setMat4("model", model1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //��������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
