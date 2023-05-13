#pragma once
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Shader.h"
#include"Camera.h"


class Light
{
public:
    Light(){}
    Light(glm::vec3 cameraPos,glm::vec3 Diffuse, glm::vec3 Ambient,
        glm::vec3 Specular, glm::vec3 Position, glm::vec3 Emission, glm::vec3 lightDirection,
        float constant, float linear, float quadratic);
    glm::vec3 cameraPos;

    glm::vec3 lightAmbient;
    glm::vec3 lightDiffuse;
    glm::vec3 lightSpecular;
    glm::vec3 lightPosition;
    glm::vec3 lightEmission;
    glm::vec3 lightDirection;

    float constant=0;
    float linear=0;
    float quadratic=0;

    int pointLightNumber = 0;
    int directionLightNumber = 0;
    int spotLightNumber = 0;

    bool isBilnn=false;
    bool useNormal=false;

    void PointLightCaculate(Shader lightShader);
    void InsertLight(Shader shader, Camera camera, glm::vec3 data[]);

};

