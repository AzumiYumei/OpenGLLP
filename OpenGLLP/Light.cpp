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


void Light::PointLightCaculate(Shader shader)
{
    this->pointLightNumber++;
    string lightName = "pointLights[" + to_string(this->pointLightNumber-1);
    shader.use();
    shader.setVec3("cameraPos", this->cameraPos);
    shader.setVec3(lightName+ "].position", this->lightPosition);
    shader.setVec3(lightName+"].ambient", this->lightAmbient);
    shader.setVec3(lightName+"].diffuse", this->lightDiffuse);
    shader.setVec3(lightName+"].specular", this->lightSpecular);
    shader.setVec3(lightName+"].emission", this->lightEmission);
    shader.setFloat(lightName+"].constant", this->constant);
    shader.setFloat(lightName+"].linear", this->linear);
    shader.setFloat(lightName+"].quadratic", this->quadratic);
    shader.setBool("isBlinn", this->isBilnn);
    shader.setBool("useNormal", this->useNormal);
    shader.setInt("PointLightNumber", this->pointLightNumber);
}

//Ìæ»»lightµÄÐÅÏ¢
void  Light::InsertLight(Shader shader,Camera camera,glm::vec3 data[])
{
    int skip = this->pointLightNumber;
    skip *= 7;

    this->cameraPos = camera.cameraPosition;

    this->lightPosition = glm::vec3(data[0 + skip]);
    this->lightDiffuse = glm::vec3(data[1 + skip]);
    this->lightAmbient = glm::vec3(data[2 + skip]);
    this->lightSpecular = glm::vec3(data[3 + skip]);
    this->lightEmission = glm::vec3(data[4 + skip]);
    this->lightDirection = glm::vec3(data[5 + skip]);
    
    this->constant = data[6 + skip].x;
    this->linear = data[6 + skip].y;
    this->quadratic = data[6 + skip].z;
    this->PointLightCaculate(shader);
}
