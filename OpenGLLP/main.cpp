
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

#define Stength 0.7f
#define Scale 10.0f

#define ViewNear 0.1f
#define ViewFar 600.0f

#pragma region Data

glm::vec3 planePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),//space

        glm::vec3(0.0f,  0.0f,  0.0f),//sun
        glm::vec3(0.5791f,  0.0f,  0.0f),//mercury
        glm::vec3(1.082f, 0.0f,  0.0f),//venus
        glm::vec3(1.496f, 0.0f,  0.0f),//earth
        glm::vec3(1.98f,  0.0f,  0.0f),//mars
        glm::vec3(2.283f, 0.0f,  0.0f),//jupiter
        glm::vec3(2.94f, 0.0f,  0.0f),//saturn
        glm::vec3(3.7099f,  0.0f,  0.0f),//uranus
        glm::vec3(4.04f,  0.0f,  0.0f),//neptune
        glm::vec3(0.38f, 0.0f,  0.0f)//moon

};

glm::vec3 planeScale[] = {
        glm::vec3(10.0f,  10.0f,  10.0f),//space

        glm::vec3(0.140f,  0.14f,  0.14f),//sun
        glm::vec3(0.0004878f,  0.0004878f,  0.0004878f),//mercury
        glm::vec3(0.0012103f,  0.0012103f,  0.0012103f),//venus
        glm::vec3(0.0012756f,  0.0012756f,  0.0012756f),//earth
        glm::vec3(0.0006794f,  0.0006794f,  0.0006794f),//mars
        glm::vec3(0.0142984f,  0.0142984f,  0.0142984f),//jupiter
        glm::vec3(0.0120536f,  0.0120536f,  0.0120536f),//saturn
        glm::vec3(0.0051120f,  0.0051120f,  0.0051120f),//uranus
        glm::vec3(0.0049528f,  0.0049528f,  0.0049528f),//neptune
        glm::vec3(0.0003700f,  0.0003700f,  0.0003700f) //moon
};

glm::vec4 planeMoveMode[] = {
    glm::vec4(0.0f,1.0f,0.0f,0.1f),//space


    glm::vec4(0.0f,1.0f,0.0f,0.1f),//sun 
    glm::vec4(0.0f,1.0f,0.0f,4.14f),  //mercur
    glm::vec4(0.0f,1.0f,0.0f,1.62f),  //venus
    glm::vec4(0.0f,1.0f,0.0f,1.0f),   //earth
    glm::vec4(0.0f,1.0f,0.0f,0.53f),   //mars
    glm::vec4(0.0f,1.0f,0.0f,0.084f),   //jupite
    glm::vec4(0.0f,1.0f,0.0f,0.034f),   //saturn
    glm::vec4(0.0f,1.0f,0.0f,0.012f),   //uranus
    glm::vec4(0.0f,1.0f,0.0f,0.006f),  //neptun
    glm::vec4(0.0f,1.0f,0.0f,13.63f)   //moon
};     

float planeSlef[] = {
    0.01,  //space      //0

    0.01,  //sun        //1
    0.0169,//mercury    //2
    0.0041,//venus      //3
    1,     //earth      //4
    1,     //mars       //5
    2.67,  //jupiter    //6
    2.4,   //saturn     //7
    1.41,  //uranus     //8
    1.5,   //neptune    //9
    0.037  //moon       //10
    
};

float drawPlane[] = {
    1,//space      //0
    
    1,//sun        //1
    5,//mercury    //2
    5,//venus      //3
    5,//earth      //4
    5,//mars       //5
    0.5,//jupiter    //6
    0.5,//saturn     //7
    0.4,//uranus     //8
    0.4,//neptune    //9
    5//moon       //10
};

//���Դ��Ϣ����
glm::vec3 pointLightData[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),//emissive
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(1.0f,0.027f,0.0028f),

    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(1.0f,0.027f,0.0028f),
};//28
//������Դ����

glm::vec3 pointLightDataEmissive[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(1.0f,0.027f,0.0028f),
};

//������̬����
glm::vec3 StaticMaterialData[] = {
    glm::vec3(0.5f, 0.5f, 0.5f),//���ʣ�������+�����⣩��ɫ
    glm::vec3(0.5f, 0.5f, 0.5f),//���ʾ��淴��
    glm::vec3(32.0f, 0.0f, 0.0f)//�߹�ȣ����������ά�����������
};

//��պ�����
vector<string> faces
{
    "right.jpg",
    "left.jpg",
    "top.jpg",
    "bottom.jpg",
    "front.jpg",
    "back.jpg"
};
#pragma endregion

#pragma region FunctionGroup
//���������
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.5f, 0.05f, 3.0f, -80.0f, 80.0f, 45.0f);
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
void LoopRanden(Shader &shader, unsigned int VAO, float near, float far)
{
    shader.use();

    shader.OpenProjection(camera, screenWeight, screenHeight, near, far);

    shader.OpenView(camera);

    //��ʼ��Ⱦ
    glBindVertexArray(VAO);
}

//����ͼ���ݽ�fragment��uniform��
void ShaderBindTexture(Shader shader,int textureCode,int shininess,bool isEmisive)
{
    shader.use();
    shader.setInt("material.diffuse", textureCode);
    shader.setInt("material.specular", textureCode);
    shader.setInt("material.emission", textureCode);
    shader.setFloat("material.shininess", shininess);
}

void Trans(Shader &shader,glm::vec3 trans,glm::vec3 scale,glm::vec4 moveMode,float self)
{
    glm::mat4 model = glm::mat4(1.0f);
    
    //��ת
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * moveMode.w * Scale), glm::vec3(moveMode.x, moveMode.y, moveMode.z));
    
    model = glm::translate(model, trans);

    //��ת
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * self * Scale), glm::vec3(moveMode.x, moveMode.y, moveMode.z));

    model = glm::scale(model, scale);

    shader.use();

    shader.setMat4("model", model);
}

void Satellite(Shader shader, glm::vec3 trans, glm::vec3 scale, glm::vec4 moveMode, 
    glm::vec4 parentMoveMode,glm::vec3 parent,float self)
{
    glm::mat4 model = glm::mat4(1.0f);

    //���ǹ�ת
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * parentMoveMode.w * Scale), glm::vec3(parentMoveMode.x, parentMoveMode.y, parentMoveMode.z));

    model = glm::translate(model, parent);

    //���ǹ�ת
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * moveMode.w * Scale), glm::vec3(moveMode.x, moveMode.y, moveMode.z));

    model = glm::translate(model, trans);

    //������ת
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * self * Scale), glm::vec3(moveMode.x, moveMode.y, moveMode.z));

    model = glm::scale(model, scale);

    shader.use();

    shader.setMat4("model", model);
}

void SkyBoxTrans(Shader shader,glm::vec3 trans,glm::vec3 scale) 
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, trans);

    model = glm::scale(model, scale);

    shader.use();

    shader.setMat4("model", model);
}

unsigned int objBindVAO(ObjLoad ObjName) 
{
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //�󶨶������
    glBindVertexArray(VAO);
    //�󶨶��㻺�����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //���������鴢�浽VAO���㻺����
    glBufferData(GL_ARRAY_BUFFER, ObjName.vertexArr.size() * sizeof(float), &ObjName.vertexArr[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ObjName.vSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, ObjName.vSize * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, ObjName.vSize * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, ObjName.vSize * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, ObjName.vSize * sizeof(float), (void*)(11 * sizeof(float)));
    glEnableVertexAttribArray(4);

    return VAO;
}
#pragma endregion

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

    //���޳�
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //����obj�ļ�����
    ObjLoad ball("ball.obj");
    ObjLoad skyBox("skyBox.obj");

#pragma region VAO&VBO&EBOBind

    //����VAO��VBO
    unsigned int VAO = objBindVAO(ball);

    unsigned int cubeVAO =objBindVAO(skyBox);
   
#pragma endregion

    //��ת����
    //stbi_set_flip_vertically_on_load(true);

    //����shader
    Shader skyShader("skyBoxVertex.vert", "skyBoxFragment.frag");//skybox
    Shader jupiterShader("lightVertex.vert", "lightFragment.frag");//jupiter
    Shader saturnShader("lightVertex.vert", "lightFragment.frag");//saturn
    Shader uranusShader("lightVertex.vert", "lightFragment.frag");//uranus
    Shader neptuneShader("lightVertex.vert", "lightFragment.frag");//neptune
    Shader marsShader("lightVertex.vert", "lightFragment.frag");//mars
    Shader spaceShader("lightVertex.vert", "lightFragment.frag");//space
    Shader sunShader("lightVertex.vert", "lightFragment.frag");//sun
    Shader mercuryShader("lightVertex.vert", "lightFragment.frag");//mercury
    Shader venusShader("lightVertex.vert", "lightFragment.frag");//venus
    Shader earthShader("lightVertex.vert", "lightFragment.frag");//earth
    Shader moonShader("lightVertex.vert", "lightFragment.frag");//moon


    //������ͼ
    Texture jupiter(0,"2k_jupiter.jpg",3,"GL_REPEAT","GL_REPEAT","GL_NEAREST","GL_NEAREST");
    Texture saturn(1, "2k_saturn.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture uranus(2,"2k_uranus.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture moon(3,"2k_moon.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture neptune(4,"2k_neptune.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture mars(5,"2k_mars.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture mercury(6,"2k_mercury.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture space(7,"2k_stars_milky_way.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture sun(8,"2k_sun.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture venus(9,"2k_venus_surface.jpg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture earth(10, "earth.jpeg", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture face(11, "awesomeface.png", 4, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    //��պ�
    Texture sky(faces);

    //����ͼ�󶨵�shader
    ShaderBindTexture(jupiterShader, jupiter.number, StaticMaterialData[2].x,false);
    ShaderBindTexture(saturnShader, saturn.number, StaticMaterialData[2].x,false);
    ShaderBindTexture(uranusShader, uranus.number, StaticMaterialData[2].x,false);
    ShaderBindTexture(moonShader, moon.number, StaticMaterialData[2].x,false);
    ShaderBindTexture(neptuneShader, neptune.number, StaticMaterialData[2].x,false);
    ShaderBindTexture(marsShader, mars.number, StaticMaterialData[2].x,false);
    ShaderBindTexture(mercuryShader, mercury.number, StaticMaterialData[2].x,false);
    ShaderBindTexture(spaceShader, space.number, StaticMaterialData[2].x,false);
    ShaderBindTexture(sunShader, sun.number, StaticMaterialData[2].x,true);
    ShaderBindTexture(venusShader, venus.number, StaticMaterialData[2].x,false);
    ShaderBindTexture(earthShader, earth.number, StaticMaterialData[2].x,false);

    skyShader.use();
    skyShader.setInt("skybox", 0);
    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        Light marsLight, mercuryLight, sunLight, spaceLight, venusLight, earthLight, jupiterLight
            , saturnLight, uranusLight, moonLight, neptuneLight,skyLight;

        //������պ�
        LoopRanden(skyShader, cubeVAO, ViewNear, ViewFar);
        SkyBoxTrans(skyShader, camera.cameraPosition, planeScale[0]);
        glBindTexture(GL_TEXTURE_CUBE_MAP, sky.textureID);
        glDrawArrays(GL_TRIANGLES, 0, skyBox.triangleSize);

        //����̫��
        sunLight.InsertLight(sunShader, camera, pointLightDataEmissive);//����ǰlight�������Ϣ��fragment
        Trans(sunShader, planePositions[1], planeScale[1] * drawPlane[1], planeMoveMode[1], planeSlef[1]);
        LoopRanden(sunShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //����ˮ��
        mercuryLight.InsertLight(mercuryShader, camera, pointLightData);//����ǰlight�������Ϣ��fragment
        Trans(mercuryShader, planePositions[2], planeScale[2] * Scale * drawPlane[2], planeMoveMode[2], planeSlef[2]);
        LoopRanden(mercuryShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //���ƽ���
        venusLight.InsertLight(venusShader, camera, pointLightData);//����ǰlight�������Ϣ��fragment
        Trans(venusShader, planePositions[3], planeScale[3] * Scale * drawPlane[3], planeMoveMode[3], planeSlef[3]);
        LoopRanden(venusShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //���Ƶ���
        earthLight.InsertLight(earthShader, camera, pointLightData);//����ǰlight�������Ϣ��fragment
        Trans(earthShader, planePositions[4], planeScale[4] * Scale * drawPlane[4], planeMoveMode[4], planeSlef[4]);
        LoopRanden(earthShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //��������
        moonLight.InsertLight(moonShader, camera, pointLightData);//����ǰlight�������Ϣ��fragment
        Satellite(moonShader, planePositions[10], planeScale[10] * Scale * drawPlane[10], planeMoveMode[10], planeMoveMode[4], planePositions[4], planeSlef[10]);
        LoopRanden(moonShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //���ƻ���
        marsLight.InsertLight(marsShader, camera, pointLightData);//����ǰlight�������Ϣ��fragment
        Trans(marsShader, planePositions[5], planeScale[5] * Scale * drawPlane[5], planeMoveMode[5], planeSlef[5]);
        LoopRanden(marsShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);
        
        //����ľ��
        jupiterLight.InsertLight(jupiterShader, camera, pointLightData);//����ǰlight�������Ϣ��fragment
        Trans(jupiterShader, planePositions[6], planeScale[6] * Scale * drawPlane[6], planeMoveMode[6], planeSlef[6]);
        LoopRanden(jupiterShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //��������
        saturnLight.InsertLight(saturnShader, camera, pointLightData);//����ǰlight�������Ϣ��fragment
        Trans(saturnShader, planePositions[7], planeScale[7] * Scale * drawPlane[7], planeMoveMode[7], planeSlef[7]);
        LoopRanden(saturnShader, VAO, 0.1f, 600.0f);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //����������
        uranusLight.InsertLight(uranusShader, camera, pointLightData);//����ǰlight�������Ϣ��fragment
        Trans(uranusShader, planePositions[8], planeScale[8] * Scale * drawPlane[8], planeMoveMode[8], planeSlef[8]);
        LoopRanden(uranusShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //���ƺ�����
        neptuneLight.InsertLight(neptuneShader, camera, pointLightData);//����ǰlight�������Ϣ��fragment
        Trans(neptuneShader, planePositions[9], planeScale[9] * Scale * drawPlane[9], planeMoveMode[9], planeSlef[9]);
        LoopRanden(neptuneShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //��������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
