#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
using namespace std;


class Texture
{
public:
	Texture(int number,string pohtoName, int channlNumber,
		string WRAP_S, string WRAP_T, string MIN_FILTER, string MAG_FILTER);

	int number;
	unsigned textureID;
	string textureName;
	int channls;
	//纹理过滤环绕方式
	string WRAP_S;
	string WRAP_T;
	string MIN_FILTER;
	string MAG_FILTER;
	// 设定超出边缘后的颜色
    float borderColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

	void creatTexture();
	void TexParamete();
private:

};

