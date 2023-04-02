#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Shader
{
public:
	unsigned int shaderID;
	// ��������ȡ��������ɫ��
	Shader(const char* vertexPath, const char* fragmentPath);
	// ʹ��/�������
	void use();
	// ���������
	void CheckCode(unsigned int id, string name);

	void setInt(const string& name, int value);

	void setFloat(const string& name, float value);



private:

};