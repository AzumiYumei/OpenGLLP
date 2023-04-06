#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Camera.h"

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

	void setMat4(const string& name, const glm::mat4& mat);

	void setVec3(const string& name,const glm::vec3& vec3);

	void OpenProjection(Camera camera, float screenWeight, float screenHeight, float near, float far);

	void OpenView(Camera camera);

private:

};