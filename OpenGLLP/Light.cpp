#include "Light.h"


Light::Light(glm::vec3 Color, glm::vec3 Diffuse, glm::vec3 Ambient,
    glm::vec3 Specular, glm::vec3 Position)
{
    this->lightColor = Color;
    this->lightAmbient = Ambient;
    this->lightDiffuse = Diffuse;
    this->lightSpecular = Specular;
    this->lightPosition = Position;
}

void Light::SimpleLightCaculate(Shader lightShader)
{
    lightShader.use();
    lightShader.setVec3("lightColor",this->lightColor );
    lightShader.setVec3("light.position", this->lightPosition);
    lightShader.setVec3("light.ambient", this->lightAmbient);
    lightShader.setVec3("light.diffuse", this->lightDiffuse);
    lightShader.setVec3("light.specular", this->lightSpecular);
}