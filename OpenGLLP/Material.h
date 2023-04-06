#pragma once
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Shader.h"

class Material
{
public:
	Material();

    glm::vec3 objectColor;
    glm::vec3 lightColor;
    glm::vec3 lightPos;
    glm::vec3 cameraPos;
    glm::vec3 materialAmbient;
    glm::vec3 materialDiffuse;
    glm::vec3 materialSpecular;
    glm::vec3 materialShininess;
    glm::vec3 lightAmbient;
    glm::vec3 lightDiffuse;
    glm::vec3 lightSpecular;
    glm::vec3 lightPos;


    lightShader.use();
    lightShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    lightShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    lightShader.setVec3("lightPos", glm::vec3(cubePositions[1].x* sin(glfwGetTime()) / 2 + 0.5,
        cubePositions[1].y* cos(glfwGetTime()) / 2 + 0.5,
        cubePositions[1].z));
    lightShader.setVec3("cameraPos", camera.cameraPosition);
    lightShader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    lightShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    lightShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightShader.setFloat("material.shininess", 32.0f);

    lightShader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    lightShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    lightShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	void SimpleLightCaculate();

private:

};
