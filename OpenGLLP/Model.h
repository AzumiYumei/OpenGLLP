#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"

#include<iostream>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include"Mesh.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    /*  ����   */
    Model(char* path)
    {
        loadModel(path);
    }
    void Draw(Shader shader);
private:
    /*  ģ������  */
    vector<Mesh> meshes;//����������Mesh������
    string directory;
    /*  ����   */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,string typeName);
};
