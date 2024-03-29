
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

glm::vec3 towerScaler[] = {
    glm::vec3(1.0f,1.0f,1.0f)
};

glm::vec4 planeMoveMode[] = {
    glm::vec4(0.0f,1.0f,0.0f,0.0f),//space


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
    0.00,  //space      //0

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

//点光源信息数组
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

glm::vec3 pointLightDataEmissive[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(Stength, Stength, Stength),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(1.0f,0.027f,0.0028f),
};

glm::vec3 pointLightPBR[] = {
    glm::vec3(1.0f,  0.0f,  0.0f),
    glm::vec3(0.9f,0.9f,0.9f),
    glm::vec3(0.9f,0.9f,0.9f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(1.0f,0.027f,0.0028f)

};
//材质球静态属性
glm::vec3 StaticMaterialData[] = {
    glm::vec3(0.5f, 0.5f, 0.5f),//材质（漫反射+环境光）颜色
    glm::vec3(0.5f, 0.5f, 0.5f),//材质镜面反射
    glm::vec3(32.0f, 0.0f, 0.0f)//高光度，后面的两个维度是无意义的
};

//天空盒索引
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
//创建摄像机
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.5f, 0.05f, 3.0f, -80.0f, 80.0f, 45.0f);
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
void LoopRanden(Shader &shader, unsigned int VAO, float near, float far)
{
    shader.use();

    shader.OpenProjection(camera, screenWeight, screenHeight, near, far);

    shader.OpenView(camera);

    //开始渲染
    glBindVertexArray(VAO);
}

//将贴图传递进fragment的uniform中
void ShaderBindTexture(Shader shader,int textureCode,int shininess)
{
    shader.use();
    shader.setInt("material.diffuse", textureCode);
    shader.setInt("material.specular", textureCode);
    shader.setInt("material.emission", textureCode);
    shader.setFloat("material.shininess", shininess);
}

void ShaderBindTexturePBR(Shader shader,int texRGB,int MTL,int EMI,int NOR,int shininess)
{
    shader.use();
    shader.setInt("material.diffuse", texRGB);
    shader.setInt("material.specular", MTL);
    shader.setInt("material.emission", EMI);
    shader.setInt("material.normal", NOR);
    shader.setFloat("material.shininess", shininess);
}

void SimTrans(Shader shader, glm::vec3 trans)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, trans);
    shader.use();
    shader.setMat4("model", model);
}

void Trans(Shader &shader,glm::vec3 trans,glm::vec3 scale,glm::vec4 moveMode,float self)
{
    glm::mat4 model = glm::mat4(1.0f);
    
    //公转
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * moveMode.w * Scale), glm::vec3(moveMode.x, moveMode.y, moveMode.z));
    
    model = glm::translate(model, trans);

    //自转
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * self * Scale), glm::vec3(moveMode.x, moveMode.y, moveMode.z));

    model = glm::scale(model, scale);

    shader.use();

    shader.setMat4("model", model);
}

void Satellite(Shader shader, glm::vec3 trans, glm::vec3 scale, glm::vec4 moveMode, 
    glm::vec4 parentMoveMode,glm::vec3 parent,float self)
{
    glm::mat4 model = glm::mat4(1.0f);

    //父星公转
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * parentMoveMode.w * Scale), glm::vec3(parentMoveMode.x, parentMoveMode.y, parentMoveMode.z));

    model = glm::translate(model, parent);

    //卫星公转
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * moveMode.w * Scale), glm::vec3(moveMode.x, moveMode.y, moveMode.z));

    model = glm::translate(model, trans);

    //卫星自转
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

    //绑定顶点对象
    glBindVertexArray(VAO);
    //绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //将顶点数组储存到VAO顶点缓冲中
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

void main1()
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

    //面剔除
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    //加载obj文件数组
    ObjLoad ball("ball.obj");
    ObjLoad skyBox("skyBox.obj");
    ObjLoad spaceBall("InverseBall.obj");

#pragma region VAO&VBO&EBOBind

    //设置VAO、VBO
    unsigned int VAO = objBindVAO(ball);

    unsigned int cubeVAO =objBindVAO(skyBox);

    unsigned int spaceVAO = objBindVAO(spaceBall);
   
#pragma endregion

    //翻转纹理
    //stbi_set_flip_vertically_on_load(true);

    //创建shader
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


    //创建贴图
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
    //天空盒
    Texture sky(faces);

    //将贴图绑定到shader
    ShaderBindTexture(jupiterShader, jupiter.number, StaticMaterialData[2].x);
    ShaderBindTexture(saturnShader, saturn.number, StaticMaterialData[2].x);
    ShaderBindTexture(uranusShader, uranus.number, StaticMaterialData[2].x);
    ShaderBindTexture(moonShader, moon.number, StaticMaterialData[2].x);
    ShaderBindTexture(neptuneShader, neptune.number, StaticMaterialData[2].x);
    ShaderBindTexture(marsShader, mars.number, StaticMaterialData[2].x);
    ShaderBindTexture(mercuryShader, mercury.number, StaticMaterialData[2].x);
    ShaderBindTexture(spaceShader, space.number, StaticMaterialData[2].x);
    ShaderBindTexture(sunShader, sun.number, StaticMaterialData[2].x);
    ShaderBindTexture(venusShader, venus.number, StaticMaterialData[2].x);
    ShaderBindTexture(earthShader, earth.number, StaticMaterialData[2].x);

    skyShader.use();
    skyShader.setInt("skybox", 0);
    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        Light marsLight, mercuryLight, sunLight, spaceLight, venusLight, earthLight, jupiterLight
            , saturnLight, uranusLight, moonLight, neptuneLight,skyLight;

        ////绘制天空盒
        //LoopRanden(skyShader, cubeVAO, ViewNear, ViewFar);
        //SkyBoxTrans(skyShader, camera.cameraPosition, planeScale[0]);
        //glBindTexture(GL_TEXTURE_CUBE_MAP, sky.textureID);
        //glDrawArrays(GL_TRIANGLES, 0, skyBox.triangleSize);

        //绘制太空
        spaceLight.InsertLight(spaceShader, camera, pointLightDataEmissive);//将当前light存入的信息给fragment
        Trans(spaceShader, planePositions[0], planeScale[0] * drawPlane[0], planeMoveMode[0], planeSlef[0]);
        LoopRanden(spaceShader, spaceVAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, spaceBall.triangleSize);

        //绘制太阳
        sunLight.InsertLight(sunShader, camera, pointLightDataEmissive);//将当前light存入的信息给fragment
        Trans(sunShader, planePositions[1], planeScale[1] * drawPlane[1], planeMoveMode[1], planeSlef[1]);
        LoopRanden(sunShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //绘制水星
        mercuryLight.InsertLight(mercuryShader, camera, pointLightData);//将当前light存入的信息给fragment
        Trans(mercuryShader, planePositions[2], planeScale[2] * Scale * drawPlane[2], planeMoveMode[2], planeSlef[2]);
        LoopRanden(mercuryShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //绘制金星
        venusLight.InsertLight(venusShader, camera, pointLightData);//将当前light存入的信息给fragment
        Trans(venusShader, planePositions[3], planeScale[3] * Scale * drawPlane[3], planeMoveMode[3], planeSlef[3]);
        LoopRanden(venusShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //绘制地球
        earthLight.InsertLight(earthShader, camera, pointLightData);//将当前light存入的信息给fragment
        Trans(earthShader, planePositions[4], planeScale[4] * Scale * drawPlane[4], planeMoveMode[4], planeSlef[4]);
        LoopRanden(earthShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //绘制月球
        moonLight.InsertLight(moonShader, camera, pointLightData);//将当前light存入的信息给fragment
        Satellite(moonShader, planePositions[10], planeScale[10] * Scale * drawPlane[10], planeMoveMode[10], planeMoveMode[4], planePositions[4], planeSlef[10]);
        LoopRanden(moonShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //绘制火星
        marsLight.InsertLight(marsShader, camera, pointLightData);//将当前light存入的信息给fragment
        Trans(marsShader, planePositions[5], planeScale[5] * Scale * drawPlane[5], planeMoveMode[5], planeSlef[5]);
        LoopRanden(marsShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);
        
        //绘制木星
        jupiterLight.InsertLight(jupiterShader, camera, pointLightData);//将当前light存入的信息给fragment
        Trans(jupiterShader, planePositions[6], planeScale[6] * Scale * drawPlane[6], planeMoveMode[6], planeSlef[6]);
        LoopRanden(jupiterShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //绘制土星
        saturnLight.InsertLight(saturnShader, camera, pointLightData);//将当前light存入的信息给fragment
        Trans(saturnShader, planePositions[7], planeScale[7] * Scale * drawPlane[7], planeMoveMode[7], planeSlef[7]);
        LoopRanden(saturnShader, VAO, 0.1f, 600.0f);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //绘制天王星
        uranusLight.InsertLight(uranusShader, camera, pointLightData);//将当前light存入的信息给fragment
        Trans(uranusShader, planePositions[8], planeScale[8] * Scale * drawPlane[8], planeMoveMode[8], planeSlef[8]);
        LoopRanden(uranusShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //绘制海王星
        neptuneLight.InsertLight(neptuneShader, camera, pointLightData);//将当前light存入的信息给fragment
        Trans(neptuneShader, planePositions[9], planeScale[9] * Scale * drawPlane[9], planeMoveMode[9], planeSlef[9]);
        LoopRanden(neptuneShader, VAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, ball.triangleSize);

        //交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
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

    //面剔除
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    //加载obj文件数组
    ObjLoad firstObj("first.obj");
    ObjLoad skyBox("skyBox.obj");
    ObjLoad secondObj("second.obj");

#pragma region VAO&VBO&EBOBind

    //设置VAO、VBO
    unsigned int firstVAO = objBindVAO(firstObj);

    unsigned int cubeVAO = objBindVAO(skyBox);

    unsigned int secondVAO = objBindVAO(secondObj);

#pragma endregion


    //创建shader
    Shader firstShader("firstVertex.vert", "firstFragment.frag");
    Shader secondShader("firstVertex.vert", "firstFragment.frag");

    Shader skyShader("skyBoxVertex.vert", "skyBoxFragment.frag");//skybox

    //翻转纹理
    //stbi_set_flip_vertically_on_load(true);
    //天空盒
    Texture sky(faces);
    stbi_set_flip_vertically_on_load(true);

    //创建贴图
    Texture firstTexRGB(0, "RGB.png", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture firstTexNOR(1, "Normal.png", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture firstTexMTL(2, "MetallicRoughnessOpacity.png", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture firstTexEMI(3, "Emissive.png", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");

    Texture secondTexRGB(4, "RGB_1.png", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture secondTexNOR(5, "Normal_3.png", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture secondTexMTL(6, "MetallicRoughnessOpacity_2.png", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");
    Texture secondTexEMI(7, "Emissive_4.png", 3, "GL_REPEAT", "GL_REPEAT", "GL_NEAREST", "GL_NEAREST");

    //将贴图绑定到shader
    ShaderBindTexturePBR(firstShader, firstTexRGB.number, firstTexMTL.number
        , firstTexEMI.number, firstTexNOR.number, StaticMaterialData[2].x);

    ShaderBindTexturePBR(secondShader, secondTexRGB.number, secondTexMTL.number
        , secondTexEMI.number, secondTexNOR.number, StaticMaterialData[2].x);

    skyShader.use();
    skyShader.setInt("skybox", 0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //绘制天空盒
        LoopRanden(skyShader, cubeVAO, ViewNear, ViewFar);
        SkyBoxTrans(skyShader, camera.cameraPosition, planeScale[0]*10.0f);
        glBindTexture(GL_TEXTURE_CUBE_MAP, sky.textureID);
        glDrawArrays(GL_TRIANGLES, 0, skyBox.triangleSize);

        Light firstLight,secondLight;

        firstLight.useNormal = true;
        firstLight.move = true;
        firstLight.InsertLight(firstShader, camera, pointLightPBR);//将当前light存入的信息给fragment
        SimTrans(firstShader, glm::vec3(1.0f));
        LoopRanden(firstShader, firstVAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, firstObj.triangleSize);

        secondLight.useNormal = true;
        secondLight.move = true;
        secondLight.InsertLight(secondShader, camera, pointLightPBR);//将当前light存入的信息给fragment
        SimTrans(secondShader, glm::vec3(1.0f));
        LoopRanden(secondShader, secondVAO, ViewNear, ViewFar);
        glDrawArrays(GL_TRIANGLES, 0, secondObj.triangleSize);

        //交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}