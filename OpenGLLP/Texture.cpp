#include"Texture.h"


Texture::Texture(string pohtoName, int channlNumber,
    string WRAPS, string WRAPT, string MINFILTER, string MAGFILTER)
{
	textureName = pohtoName;
	channls = channlNumber;

    string WRAP_S=WRAPS;
    string WRAP_T=WRAPT;
    string MIN_FILTER=MINFILTER;
    string MAG_FILTER=MAGFILTER;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    TexParamete();
 
    creatTexture();
}

void Texture::TexParamete()
{
    //S方向的纹理环绕方式
    if(WRAP_S=="GL_REPEAT")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    else if (WRAP_S == "GL_MIRRORED_REPEAT")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    else if (WRAP_S == "GL_CLAMP_TO_EDGE")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    else if (WRAP_S == "GL_CLAMP_TO_BORDER")
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    

    //T方向的纹理环绕方式
    if (WRAP_T == "GL_REPEAT")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    else if (WRAP_T == "GL_MIRRORED_REPEAT")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    else if (WRAP_T == "GL_CLAMP_TO_EDGE")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    else if (WRAP_T == "GL_CLAMP_TO_BORDER")
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    

    //缩小时的纹理过滤
    if (MIN_FILTER == "GL_LINEAR")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    else if (MIN_FILTER == "GL_NEAREST")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    else if (MIN_FILTER == "GL_NEAREST_MIPMAP_NEAREST")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    else if (MIN_FILTER == "GL_LINEAR_MIPMAP_NEAREST")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    else if (MIN_FILTER == "GL_NEAREST_MIPMAP_LINEAR")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    else if (MIN_FILTER == "GL_LINEAR_MIPMAP_LINEAR")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //放大时的纹理过滤
    if (MAG_FILTER == "GL_LINEAR")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    else if (MAG_FILTER == "GL_NEAREST")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    else if (MAG_FILTER == "GL_NEAREST_MIPMAP_NEAREST")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    else if (MAG_FILTER == "GL_LINEAR_MIPMAP_NEAREST")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    else if (MAG_FILTER == "GL_NEAREST_MIPMAP_LINEAR")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    else if (MAG_FILTER == "GL_LINEAR_MIPMAP_LINEAR")
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void Texture::creatTexture()
{   
    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char* data = stbi_load(textureName.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        if(channls==3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if (channls == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}