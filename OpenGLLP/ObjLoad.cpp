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
    std::vector<Face> numsFace;
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

                numsFace.push_back(temp[0]);
                numsFace.push_back(temp[1]);
                numsFace.push_back(temp[2]);
            }

            if (n / 2 == 4)
            {
                iss >> c >> temp[0].vertex >> c >> temp[0].uv >> c >> temp[0].normal
                    >> temp[1].vertex >> c >> temp[1].uv >> c >> temp[1].normal
                    >> temp[2].vertex >> c >> temp[2].uv >> c >> temp[2].normal
                    >> temp[3].vertex >> c >> temp[3].uv >> c >> temp[3].normal;

                numsFace.push_back(temp[0]);
                numsFace.push_back(temp[1]);
                numsFace.push_back(temp[2]);
                numsFace.push_back(temp[2]);
                numsFace.push_back(temp[3]);
                numsFace.push_back(temp[0]);
            }
        }
    }

    in.close();

    for (Face num : numsFace)
    {
        VAOArr.push_back(numsXYZ[num.vertex - 1].x);
        VAOArr.push_back(numsXYZ[num.vertex - 1].y);
        VAOArr.push_back(numsXYZ[num.vertex - 1].z);

        VAOArr.push_back(numsNor[num.normal - 1].x);
        VAOArr.push_back(numsNor[num.normal - 1].y);
        VAOArr.push_back(numsNor[num.normal - 1].z);

        VAOArr.push_back(numsUV[num.uv - 1].u);
        VAOArr.push_back(numsUV[num.uv - 1].v);
    }

    this->triangleSize = numsFace.size();

    return VAOArr;
}