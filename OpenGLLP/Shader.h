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
	// 构造器读取并构建着色器
	Shader(const char* vertexPath, const char* fragmentPath);
	// 使用/激活程序
	void use();
	// 编码检查程序
	void CheckCode(unsigned int id, string name);

	void setInt(const string& name, int value);

	void setFloat(const string& name, float value);



private:

};