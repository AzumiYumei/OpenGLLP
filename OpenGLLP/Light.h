#pragma once
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Shader.h"


class Light
{
public:
    Light(glm::vec3 Color, glm::vec3 Diffuse, glm::vec3 Ambient,
        glm::vec3 Specular, glm::vec3 Position, glm::vec3 Emission, glm::vec3 lightDirection,
        float constant, float linear, float quadratic);
    
    glm::vec3 zero = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 one = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec3 lightColor;
    glm::vec3 lightAmbient;
    glm::vec3 lightDiffuse;
    glm::vec3 lightSpecular;
    glm::vec3 lightPosition;
    glm::vec3 lightEmission; 
    glm::vec3 lightDirection;

    float constant;
    float linear;
    float quadratic;

    void SimpleLightCaculate(Shader lightShader);

};

