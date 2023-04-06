#pragma once
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Shader.h"
#include"Light.h"

class Material
{
public:
	Material(glm::vec3 objectColor,glm::vec3 cameraPos,int shininess,glm::vec3 specular);


    glm::vec3 objectColor;
    glm::vec3 cameraPos;
    glm::vec3 materialAmbient;
    glm::vec3 materialDiffuse;
    glm::vec3 materialSpecular;
    int materialShininess;

	void SimpleMaterialCaculate(Shader lightShader);

private:

};
