#include "Light.h"


Light::Light(glm::vec3 cameraPos,glm::vec3 Diffuse, glm::vec3 Ambient,
    glm::vec3 Specular, glm::vec3 Position, glm::vec3 Emission, glm::vec3 lightDirection,
    float constant,float linear,float quadratic)
{
    this->lightAmbient = Ambient;
    this->lightDiffuse = Diffuse;
    this->lightSpecular = Specular;
    this->lightPosition = Position;
    this->lightEmission = Emission;
    this->lightDirection = lightDirection;

    this->constant= constant;
    this->linear= linear;
    this->quadratic= quadratic;

    this->cameraPos = cameraPos;
    
}

void Light::PointLightCaculate(Shader lightShader)
{
    this->pointLightNumber++;
    string lightName = "pointLights[" + to_string(this->pointLightNumber-1);
    lightShader.use();
    lightShader.setVec3("cameraPos", this->cameraPos);
    lightShader.setVec3(lightName+ "].position", this->lightPosition);
    lightShader.setVec3(lightName+"].ambient", this->lightAmbient);
    lightShader.setVec3(lightName+"].diffuse", this->lightDiffuse);
    lightShader.setVec3(lightName+"].specular", this->lightSpecular);
    lightShader.setVec3(lightName+"].emission", this->lightEmission);
    lightShader.setFloat(lightName+"].constant", this->constant);
    lightShader.setFloat(lightName+"].linear", this->linear);
    lightShader.setFloat(lightName+"].quadratic", this->quadratic);
    lightShader.setInt("PointLightNumber", this->pointLightNumber);
}
