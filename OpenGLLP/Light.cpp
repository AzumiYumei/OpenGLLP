#include "Light.h"

glm::vec3 TranslateV3(glm::vec3 position, int mode);

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

//�滻light����Ϣ
void  Light::InsertLight(Shader shader,Camera camera,glm::vec3 data[])
{
    int skip = this->pointLightNumber;
    skip *= 7;
    //cout << skip<<endl;

    this->cameraPos = camera.cameraPosition;

    this->lightPosition = TranslateV3(data[0 + skip], 3);//���ݹ��λ�����ɹ�
    //light.lightPosition = glm::vec3(data[0 + skip]);//���ݹ��λ�����ɹ�


    this->lightDiffuse = glm::vec3(data[1 + skip]);
    this->lightAmbient = glm::vec3(data[2 + skip]);
    this->lightSpecular = glm::vec3(data[3 + skip]);
    this->lightEmission = glm::vec3(data[4 + skip]);
    this->lightDirection = glm::vec3(data[5 + skip]);
    
    this->constant = data[6 + skip].x;
    this->linear = data[6 + skip].y;
    this->quadratic = data[6 + skip].z;
    this->PointLightCaculate(shader);
    //cout << light.pointLightNumber << endl;
}


glm::vec3 TranslateV3(glm::vec3 position, int mode)
{
    glm::vec3 trans;
    if (mode == 1)//��z����ת
    {
        trans = glm::vec3(position.x * sin(glfwGetTime()) / 2 + 0.5,
            position.y * cos(glfwGetTime()) / 2 + 0.5, position.z);
    }
    else if (mode == 2)//��y����ת
    {
        trans = glm::vec3(position.x * sin(glfwGetTime()) / 2 + 0.5,
            position.y, position.z * cos(glfwGetTime()) / 2 + 0.5);
    }
    else if (mode == 3)//��x����ת
    {
        trans = glm::vec3(position.x
            , position.y * sin(glfwGetTime()) / 2 + 0.5,
            position.z * cos(glfwGetTime()) / 2 + 0.5);
    }

    return trans;
}
