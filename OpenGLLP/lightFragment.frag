#version 330 core
out vec4 FragColor;

struct Material {
//由贴图控制的
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    sampler2D normal;
    float shininess;
}; 


struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define MAX_NUMBER 100
uniform int PointLightNumber;


uniform vec3 cameraPos;
uniform DirLight dirLight;
uniform PointLight pointLights[MAX_NUMBER];
uniform SpotLight spotLight;


uniform Material material;

uniform bool isBlinn;
uniform bool useNormal;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in mat3 TBN;

vec3 PointLightFunction(PointLight light,vec3 Normal,Material material,vec3 FragPos);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 result;
    //平行光
    result = CalcDirLight(dirLight, Normal, cameraPos);
    for(int i=0;i<PointLightNumber;i++)
        result += PointLightFunction( pointLights[i], Normal, material , FragPos);
    
    FragColor = vec4(result, 1.0);
}

vec3 PointLightFunction(PointLight light,vec3 Normal,Material material,vec3 FragPos)
{
    vec3 norm;//储存面法线向量
    if(useNormal)
    {
        norm = texture(material.normal,TexCoords).rgb;
        // 将法线向量转换为范围[-1,1]
        norm = normalize(norm * 2.0 - 1.0);
        norm = normalize(TBN * norm);
    }
    else
    {
        norm = normalize(Normal);//储存面法线向量
    }

    //漫反射
    vec3 lightDir = normalize(light.position - FragPos);//获取物体指向光源的向量
    float diff = max(dot(norm, lightDir), 0.0);//将面法线向量与光线向量的夹角的值diff，如果小于0，则为0
    
    //镜面反射
    vec3 viewDir = normalize(cameraPos - FragPos);//计算物体指向摄象机的向量
    float spec;
    if(isBlinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    }
    else
    {
        vec3 reflectDir = reflect(-lightDir, norm);  //将光源指向物体的向量与法线放在一起计算反射光向量
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//计算高光大小
    }

    //将漫反射的颜色（一般与物体颜色一致），乘于diff，乘于贴图的rgb颜色，得到漫反射
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    // 环境光,使用贴图的rgb计算环境光
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    //将反射光的颜色（一般与光源颜色一致），乘于高光大小，乘于贴图的rgb颜色，得到镜面反射
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    //自发光
    vec3 emission = light.emission * texture(material.emission,TexCoords).rgb;

    //衰减
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;
    
    //将三者的反射光叠加在一起得到最终的经验模型
    vec3 result=ambient + diffuse + specular + emission;
        
    return result;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 cameraPos)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(cameraPos, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

