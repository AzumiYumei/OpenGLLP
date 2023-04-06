#include "Light.h"


Light::Light(glm::vec3 Color, glm::vec3 Diffuse, glm::vec3 Ambient,
    glm::vec3 Specular, glm::vec3 Position, glm::vec3 Emission, glm::vec3 lightDirection,
    float constant,float linear,float quadratic)
{
    this->lightColor = Color;
    this->lightAmbient = Ambient;
    this->lightDiffuse = Diffuse;
    this->lightSpecular = Specular;
    this->lightPosition = Position;
    this->lightEmission = Emission;
    this->lightDirection = lightDirection;

    this->constant= constant;
    this->linear= linear;
    this->quadratic= quadratic;
}

void Light::SimpleLightCaculate(Shader lightShader)
{
    lightShader.use();
    lightShader.setVec3("lightColor",this->lightColor );
    lightShader.setVec3("light.position", this->lightPosition);
    lightShader.setVec3("light.ambient", this->lightAmbient);
    lightShader.setVec3("light.diffuse", this->lightDiffuse);
    lightShader.setVec3("light.specular", this->lightSpecular);
    lightShader.setVec3("light.emission", this->lightEmission);
    lightShader.setVec3("light.direction", this->lightDirection);
    lightShader.setFloat("light.constant", this->constant);
    lightShader.setFloat("light.linear", this->linear);
    lightShader.setFloat("light.quadratic", this->quadratic);
}