#include "ObjLoad.h"

struct VertexArr
{
    float x, y, z;
};

struct UVArr
{
    float u,v;
};

struct NormalArr
{
    float x, y, z;
};

struct Face
{
    int vertex, uv, normal;
};

ObjLoad::ObjLoad(string objName)
{
    this->obj = objName;
    this->vertexArr = Load();
}

void PushVAO(std::vector<float>& VAOArr, Face temp, std::vector<NormalArr> numsNor,
    std::vector<UVArr> numsUV, std::vector<VertexArr> numsXYZ, glm::vec3 Tangent,
    glm::vec3 BiTangent)
{
    VAOArr.push_back(numsXYZ[temp.vertex - 1].x);
    VAOArr.push_back(numsXYZ[temp.vertex - 1].y);
    VAOArr.push_back(numsXYZ[temp.vertex - 1].z);

    VAOArr.push_back(numsNor[temp.normal - 1].x);
    VAOArr.push_back(numsNor[temp.normal - 1].y);
    VAOArr.push_back(numsNor[temp.normal - 1].z);

    VAOArr.push_back(numsUV[temp.uv - 1].u);
    VAOArr.push_back(numsUV[temp.uv - 1].v);

    VAOArr.push_back(Tangent.x);
    VAOArr.push_back(Tangent.y);
    VAOArr.push_back(Tangent.z);

    VAOArr.push_back(BiTangent.x);
    VAOArr.push_back(BiTangent.y);
    VAOArr.push_back(BiTangent.z);
}


void CreatTangent(std::vector<float>& VAOArr, std::vector<NormalArr> numsNor, 
    Face temp1, Face temp2, Face temp3,std::vector<VertexArr> numsXYZ,
    std::vector<UVArr> numsUV)
{
    glm::vec3 edge1, edge2;

    glm::vec2 deltaUV1, deltaUV2;

    glm::vec3 Tangent, BiTangent;

    VertexArr Pos[3];
    UVArr UV[3];

    Pos[0] = numsXYZ[temp1.vertex - 1];
    Pos[1] = numsXYZ[temp2.vertex - 1];
    Pos[2] = numsXYZ[temp3.vertex - 1];

    UV[0] = numsUV[temp1.uv - 1];
    UV[1] = numsUV[temp2.uv - 1];
    UV[2] = numsUV[temp3.uv - 1];

    edge1.x = Pos[1].x - Pos[0].x;
    edge1.y = Pos[1].y - Pos[0].y;
    edge1.z = Pos[1].z - Pos[0].z;

    edge2.x = Pos[2].x - Pos[0].x;
    edge2.y = Pos[2].y - Pos[0].y;
    edge2.z = Pos[2].z - Pos[0].z;

    deltaUV1.x = UV[1].u - UV[0].u;
    deltaUV1.y = UV[1].v - UV[0].v;

    deltaUV2.x = UV[2].u - UV[0].u;
    deltaUV2.y = UV[2].v - UV[0].v;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    Tangent.x = f * (deltaUV2.x * edge1.x - deltaUV1.y * edge2.x);
    Tangent.y = f * (deltaUV2.x * edge1.y - deltaUV1.y * edge2.y);
    Tangent.z = f * (deltaUV2.x * edge1.z - deltaUV1.y * edge2.z);
    Tangent = glm::normalize(Tangent);

    BiTangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.y * edge2.x);
    BiTangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.y * edge2.y);
    BiTangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.y * edge2.z);
    BiTangent = glm::normalize(BiTangent);

    PushVAO(VAOArr, temp1, numsNor, numsUV, numsXYZ, Tangent, BiTangent);
    PushVAO(VAOArr, temp2, numsNor, numsUV, numsXYZ, Tangent, BiTangent);
    PushVAO(VAOArr, temp3, numsNor, numsUV, numsXYZ, Tangent, BiTangent);
}


vector<float> ObjLoad::Load()
{
    std::ifstream in(this->obj);
    if (!in)
    {
        std::cerr << "Cannot open file!" << std::endl;
        exit(0);
    }

    std::vector<VertexArr> numsXYZ;
    std::vector<UVArr> numsUV;
    std::vector<NormalArr> numsNor;
    std::string line;
    std::vector<float> VAOArr;

    std::string s;

    char c;

    while (getline(in, line)) {
        if (line[0] == 'v')
        {
            if (line[1] == 't')
            {
                UVArr temp;
                std::istringstream iss(line);
                iss >> s >> temp.u >> temp.v;
                numsUV.push_back(temp);
                // 获取一个uv坐标(u, v)
            }
            else if (line[1] == 'n')
            {
                NormalArr temp;
                std::istringstream iss(line);
                iss >> s >> temp.x >> temp.y >> temp.z;
                numsNor.push_back(temp);
                // 获取一个法线坐标(x,y,z)
            }
            else
            {
                VertexArr temp;
                std::istringstream iss(line);
                iss >> s >> temp.x >> temp.y >> temp.z;

                numsXYZ.push_back(temp);
                // 获取一个顶点坐标(x, y, z)
            }
        }

        if (line[0] == 'f')
        {
            // 获取面信息字符串
            std::string faceStr = line.substr(2);

            // 统计/的个数,即顶点个数n
            int n = std::count(faceStr.begin(), faceStr.end(), '/');

            Face* temp = new Face[n / 2];
            std::istringstream iss(line);

            if (n / 2 == 3)
            {
                iss >> c >> temp[0].vertex >> c >> temp[0].uv >> c >> temp[0].normal
                    >> temp[1].vertex >> c >> temp[1].uv >> c >> temp[1].normal
                    >> temp[2].vertex >> c >> temp[2].uv >> c >> temp[2].normal;

                //利用索引将数据存入VAO，计算切线空间,也存入VAO
                CreatTangent(VAOArr,numsNor,temp[0], temp[1], temp[2],numsXYZ, numsUV);
            }

            if (n / 2 == 4)
            {
                iss >> c >> temp[0].vertex >> c >> temp[0].uv >> c >> temp[0].normal
                    >> temp[1].vertex >> c >> temp[1].uv >> c >> temp[1].normal
                    >> temp[2].vertex >> c >> temp[2].uv >> c >> temp[2].normal
                    >> temp[3].vertex >> c >> temp[3].uv >> c >> temp[3].normal;

                //利用索引将数据存入VAO，计算切线空间,也存入VAO
                CreatTangent(VAOArr,numsNor,temp[0], temp[1], temp[2], numsXYZ, numsUV);

                //利用索引将数据存入VAO，计算切线空间,也存入VAO
                CreatTangent(VAOArr, numsNor,temp[2], temp[3], temp[0],numsXYZ, numsUV);
            }
        }
    }

    in.close();
    this->vSize = 14;//vertex:3,normal:3,uv:2,tangent:3,bitangent:3
    this->triangleSize = VAOArr.size()/this->vSize;

    return VAOArr;
}