#include<GL/glew.h>
#include<GLFW/glfw3.h>


#include<iostream>
using namespace std;


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{
public:
	unsigned textureID;
	string textureName;
	int channls;
	//������˻��Ʒ�ʽ
	string WRAP_S;
	string WRAP_T;
	string MIN_FILTER;
	string MAG_FILTER;
	// �趨������Ե�����ɫ
    float borderColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };


	Texture(string pohtoName,int channlNumber, 
		string WRAP_S, string WRAP_T , string MIN_FILTER, string MAG_FILTER);
	void creatTexture();
	void TexParamete();

private:

};

