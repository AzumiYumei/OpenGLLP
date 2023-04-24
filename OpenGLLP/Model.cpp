#include"Model.h"

//��������mesh��������������Լ�����Ⱦ����
void Model::Draw(Shader shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}

void Model::loadModel(string path)
{// ����assimp��ȡģ���ļ�
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // ���ģ�͵����Ƿ���ȷ
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    // ��ȡ�ļ�Ŀ¼·��
    directory = path.substr(0, path.find_last_of('/'));

    // ��ȡ��scene�����scene�ĸ��ڵ�
    processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode* node, const aiScene* scene)
{
    // ����ڵ����е���������еĻ���
    for (unsigned int i = 0; i < node->mNumMeshes; i++)//mNumMeshes�����˵�ǰnode�ڵ㴢�����������
    {
        //��assimp�����ʽ��ȡ��ǰ����mesh
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //�Ե�ǰmesh���д���
        meshes.push_back(processMesh(mesh, scene));
    }
    // �������������ӽڵ��ظ���һ����
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) 
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        //��ȡmesh�еĶ��㣬����vertex
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        //��ȡmesh�еķ�����Ϣ
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        //��ȡmesh�е���������
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 UV;
        }

    }

}
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{

}