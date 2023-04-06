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
	Light(glm::vec3 lightColor, glm::vec3 lightDiffuse, glm::vec3 lightAmbient,
        glm::vec3 lightSpecular,glm::vec3 lightPosition);

    glm::vec3 lightColor;
    glm::vec3 lightAmbient;
    glm::vec3 lightDiffuse;
    glm::vec3 lightSpecular;
    glm::vec3 lightPosition;

    void SimpleLightCaculate(Shader lightShader);

};

