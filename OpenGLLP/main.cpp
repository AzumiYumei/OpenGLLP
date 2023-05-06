
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
#include"ObjLoad.h"
using namespace std;

#include<iostream>
#include<string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int screenWeight = 1200;
int screenHeight = 1200;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool isFirstOpen = true;

float lastX = screenWeight / 2.0f;
float lastY = screenHeight / 2.0f;

#define Stength 0.2f

//顶点与法向数组
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

//测试盒子位置信息
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

//点光源信息数组
glm::vec3 pointLightData[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(1.0f,0.09f,0.032f),

    glm::vec3(2.3f, -3.3f, -4.0f),
  glm::vec3(Stength, Stength, Stength),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(1.0f,0.027f,0.0028f),

    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(1.0f,0.027f,0.0028f),

    glm::vec3(0.0f,  0.0f, -3.0f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(1.0f,0.027f,0.0028f)
};//28
//计算点光源数量
int pointLightNumber = sizeof(pointLightData) / sizeof(glm::vec3)/7;

//材质球静态属性
glm::vec3 StaticMaterialData[] = {
    glm::vec3(1.0f, 0.5f, 0.31f),//材质（漫反射+环境光）颜色
    glm::vec3(0.5f, 0.5f, 0.5f),//材质镜面反射
    glm::vec3(32.0f, 0.0f, 0.0f)//高光度，后面的两个维度是无意义的
};

//创建摄像机
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.5f, 0.05f, 3.0f, -80.0f, 80.0f,45.0f);
//单位帧时间差
float DeletaTime()
{
    deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();
    return deltaTime;
}
//键盘输入
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
//鼠标输入
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
//滚轮输入
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
//主循环渲染组
void LoopRanden(Shader shader, unsigned int VAO, float near, float far)
{
    shader.use();

    shader.OpenProjection(camera, screenWeight, screenHeight, near, far);

    shader.OpenView(camera);

    //开始渲染
    glBindVertexArray(VAO);
}

glm::mat4 TranslateM4(glm::vec3 position, int mode)
{
    glm::mat4 model = glm::mat4(1.0f);
    if (mode == 1)//绕z轴旋转
    {
        model = glm::translate(model, glm::vec3(position.x * sin(glfwGetTime()) / 2 + 0.5,
            position.y * cos(glfwGetTime()) / 2 + 0.5, position.z));
    }
    else if (mode == 2)//绕y轴旋转
    {
        model = glm::translate(model, glm::vec3(position.x * sin(glfwGetTime()) / 2 + 0.5,
            position.y, position.z * cos(glfwGetTime()) / 2 + 0.5));
    }
    else if (mode == 3)//绕x轴旋转
    {
        model = glm::translate(model, glm::vec3(position.x ,
            position.y * sin(glfwGetTime()) / 2 + 0.5, 
            position.z * cos(glfwGetTime()) / 2 + 0.5));
    }
    else if (mode == 4)//缩放
    {
        model = glm::translate(model, glm::vec3(position.x,
            position.y * sin(glfwGetTime()) / 2 + 0.5,
            position.z * cos(glfwGetTime()) / 2 + 0.5));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    }

    return model;
}

void textNotLighting(Shader shader,unsigned int VAO)
{
    shader.use();
    LoopRanden(shader, VAO, 0.1f, 100.0f);
    for (int i = 1; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

Material CreateMaterial()
{
    glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 materialSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
    int materialShininess = 32;

    Material material(objectColor, materialSpecular, materialShininess);

    return material;
}

void main()
{
#pragma region WindowCrate&Init

    //初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    //创建窗口
    GLFWwindow* window = glfwCreateWindow(screenWeight, screenHeight, "LearnOpenGL", NULL, NULL);

    glViewport(0, 0, screenWeight, screenHeight);

    //如果不加上下面两条公式，那么就内存分配就会出错
    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        printf("Error\n");

#pragma endregion

    //监听鼠标信息
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //打开深度测试
    glEnable(GL_DEPTH_TEST);

    //加载obj文件数组
    ObjLoad ball("ball.obj");

#pragma region VAO&VBO&EBOBind

    //设置VAO、VBO、EBO、光照VAO
    unsigned int VAO, VBO, lightVAO ,cubeVAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //绑定顶点对象
    glBindVertexArray(VAO);
    //绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //将顶点数组储存到VAO顶点缓冲中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data[0], GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);  
    */

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
   

#pragma endregion

    //创建shader
    Shader lightShader("lightVertex.vert", "lightFragment.frag");//光照shader
    Shader cubeShader("cubeVertex.txt","cubeFragment.txt");//发光方块shader

    //翻转纹理
    stbi_set_flip_vertically_on_load(true);

    //创建贴图
    Texture texture1("wall.jpg",3,"GL_REPEAT","GL_REPEAT","GL_NEAREST","GL_NEAREST");
    Texture texture2( "awesomeface.png", 4, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture texture3("container2.png", 4, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture texture4("container2_specular.png", 4, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture texture5("matrix.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture texture6("2k_mars.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture texture7("2k_mercury.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture texture8("2k_stars_milky_way.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture texture9("2k_sun.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture texture10("2k_venus_surface.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");

    
    //将贴图传递进fragment的uniform中
    lightShader.use();
    lightShader.setInt("material.diffuse1", 2);
    lightShader.setInt("material.specular1", 3);
    lightShader.setInt("material.emission", 4);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        //将纹理绑定到纹理单元，使用纹理单元就不必传入uniform也能使用
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1.textureID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2.textureID);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3.textureID);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture4.textureID);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, texture5.textureID);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, texture6.textureID);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, texture7.textureID);


        //材质设定
        Material material(StaticMaterialData[0],StaticMaterialData[1],StaticMaterialData[2].x);
        material.SimpleMaterialCaculate(lightShader);

        
        Light light;
        //InsertLight(lightShader,light,lightData);//将当前light存入的信息给fragment
        light.InsertLight(lightShader, camera, pointLightData);//将当前light存入的信息给fragment
        light.InsertLight(lightShader, camera, pointLightData);//将当前light存入的信息给fragment



        //创建盒子
        //渲染部分一
        LoopRanden(lightShader, lightVAO, 0.1f, 100.0f);
        for (int i = 1; i < 10; i++)
        {
             glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
            lightShader.setMat4("model", model);
            //渲染部分二
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //创建光盒
        LoopRanden(cubeShader, cubeVAO, 0.1f, 100.0f);
        for (int i = 0; i < light.pointLightNumber; i++)//根据点光的生成数量和生成位置相应的生成光盒
        {
            glm::mat4 model;
            model = TranslateM4(pointLightData[i * 7], 4);


            cubeShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
