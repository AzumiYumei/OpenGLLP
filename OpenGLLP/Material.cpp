#include"Material.h"

Material::Material(glm::vec3 objectColor, glm::vec3 cameraPos, glm::vec3 specular, int shininess)
{
    this->objectColor=objectColor;
    this->cameraPos=cameraPos;
    this->materialAmbient=objectColor;
    this->materialDiffuse=objectColor;
    this->materialSpecular=specular;
    this->materialShininess=shininess;
}

void Material::SimpleMaterialCaculate(Shader lightShader)
{
    lightShader.use();
    lightShader.setVec3("objectColor", this->objectColor);
    lightShader.setVec3("cameraPos", this->cameraPos);
    lightShader.setVec3("material.ambient", this->objectColor);
    lightShader.setVec3("material.diffuse", this->objectColor);
    lightShader.setVec3("material.specular", this->materialSpecular);
    lightShader.setFloat("material.shininess", this->materialShininess);
}

