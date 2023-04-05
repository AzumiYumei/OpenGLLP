#include"Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. 从文件路径中获取顶点/片段着色器
    string vertexCode;
    string fragmentCode;
    ifstream vertexShaderFile;
    ifstream fragmentShaderFile;
    // 保证ifstream对象可以抛出异常：
    vertexShaderFile.exceptions(ifstream::failbit || ifstream::badbit);
    fragmentShaderFile.exceptions(ifstream::failbit || ifstream::badbit);
    try
    {
        if (!vertexShaderFile.is_open()||!fragmentShaderFile.is_open())
        // 打开文件
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // 关闭文件处理器
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // 转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();

    // 2. 编译着色器
    unsigned int vertex, fragment;

    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, NULL);
    glCompileShader(vertex);
    CheckCode(vertex, "SHADER");

    // 片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragment);
    CheckCode(fragment, "SHADER");


    // 着色器程序
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, fragment);
    glLinkProgram(shaderID);
    CheckCode(shaderID, "PROGRAM");


    // 删除着色器
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::use()
{
    glUseProgram(shaderID);
}

void Shader:: CheckCode(unsigned int id, string name)
{
    int success;
    char infoLog[512];
    if (name=="SHADER")
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
    }
    if (name=="PROGRAM")
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

    }
}

void Shader::setInt(const string& name, int value) 
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}
void Shader::setFloat(const string& name, float value)
{
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}
void Shader::setMat4(const std::string& name, const glm::mat4& mat) 
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setVec3(const string& name, const glm::vec3& vec3)
{
    glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &vec3[0]);
}


void Shader::OpenProjection(Camera camera,float screenWeight,float screenHeight,float near,float far)
{
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), screenWeight / screenHeight, near, far);
    setMat4("projection", projection);
}

void Shader::OpenView(Camera camera)
{
    glm::mat4 view = camera.GetViewMatrix();
    setMat4("view", view);

}


