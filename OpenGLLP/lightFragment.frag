#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
}; 

struct Light {
    vec3 direction;//平行光
    vec3 position;//点光源
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;

    //点光源衰减
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 cameraPos;

uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

vec3 PointLight(Light light,vec3 Normal,Material material,vec3 FragPos);

vec3 AttenuationFunction(vec3 ambient,vec3 diffuse,vec3 specular);
vec3 DiffuseFunction(Light light,vec3 Normal,Material material,vec3 FragPos);
vec3 SpecularFunction(Light light,vec3 Normal,Material material,vec3 FragPos);

void main()
{
    //平行光
    //vec3 lightDir = normalize(-light.direction);

    vec3 result =PointLight( light, Normal, material,FragPos);

    FragColor = vec4(result, 1.0);
}

vec3 PointLight(Light light,vec3 Normal,Material material,vec3 FragPos)
{
    // 环境光,使用贴图的rgb计算环境光
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    vec3 diffuse = DiffuseFunction(light,Normal,material,FragPos);

    vec3 specular = SpecularFunction(light,Normal,material,FragPos);

    vec3 result = AttenuationFunction(ambient,diffuse, specular);//将三者的反射光叠加在一起得到最终的经验模型

    return result;
}

 // 漫反射 
vec3 DiffuseFunction(Light light,vec3 Normal,Material material,vec3 FragPos)
{
    vec3 norm = normalize(Normal);//储存面法线向量
    vec3 lightDir = normalize(light.position - FragPos);//获取物体指向光源的向量
    float diff = max(dot(norm, lightDir), 0.0);//将面法线向量与光线向量的夹角的值diff，如果小于0，则为0
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;//将漫反射的颜色（一般与物体颜色一致），乘于diff，乘于贴图的rgb颜色，得到漫反射
    
    return diffuse;
}

 // 镜面反射
vec3 SpecularFunction(Light light,vec3 Normal,Material material,vec3 FragPos)
{
    vec3 norm = normalize(Normal);//储存面法线向量
    vec3 lightDir = normalize(light.position - FragPos);//获取物体指向光源的向量

    vec3 viewDir = normalize(cameraPos - FragPos);//计算物体指向摄象机的向量
    vec3 reflectDir = reflect(-lightDir, norm);  //将光源指向物体的向量与法线放在一起计算反射光向量
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//计算高光大小
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;//将反射光的颜色（一般与光源颜色一致），乘于高光大小，乘于贴图的rgb颜色，得到镜面反射

    return specular;
}

 //衰减函数
vec3 AttenuationFunction(vec3 ambient,vec3 diffuse,vec3 specular)
{
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;   

    return  (ambient + diffuse + specular );//将三者的反射光叠加在一起得到最终的经验模型
}
