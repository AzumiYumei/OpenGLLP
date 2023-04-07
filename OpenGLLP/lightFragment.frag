#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
}; 

struct Light {
    vec3 direction;//ƽ�й�
    vec3 position;//���Դ
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;

    //���Դ˥��
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
    //ƽ�й�
    //vec3 lightDir = normalize(-light.direction);

    vec3 result =PointLight( light, Normal, material,FragPos);

    FragColor = vec4(result, 1.0);
}

vec3 PointLight(Light light,vec3 Normal,Material material,vec3 FragPos)
{
    // ������,ʹ����ͼ��rgb���㻷����
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    vec3 diffuse = DiffuseFunction(light,Normal,material,FragPos);

    vec3 specular = SpecularFunction(light,Normal,material,FragPos);

    vec3 result = AttenuationFunction(ambient,diffuse, specular);//�����ߵķ���������һ��õ����յľ���ģ��

    return result;
}

 // ������ 
vec3 DiffuseFunction(Light light,vec3 Normal,Material material,vec3 FragPos)
{
    vec3 norm = normalize(Normal);//�����淨������
    vec3 lightDir = normalize(light.position - FragPos);//��ȡ����ָ���Դ������
    float diff = max(dot(norm, lightDir), 0.0);//���淨����������������ļнǵ�ֵdiff�����С��0����Ϊ0
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;//�����������ɫ��һ����������ɫһ�£�������diff��������ͼ��rgb��ɫ���õ�������
    
    return diffuse;
}

 // ���淴��
vec3 SpecularFunction(Light light,vec3 Normal,Material material,vec3 FragPos)
{
    vec3 norm = normalize(Normal);//�����淨������
    vec3 lightDir = normalize(light.position - FragPos);//��ȡ����ָ���Դ������

    vec3 viewDir = normalize(cameraPos - FragPos);//��������ָ�������������
    vec3 reflectDir = reflect(-lightDir, norm);  //����Դָ������������뷨�߷���һ����㷴�������
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//����߹��С
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;//����������ɫ��һ�����Դ��ɫһ�£������ڸ߹��С��������ͼ��rgb��ɫ���õ����淴��

    return specular;
}

 //˥������
vec3 AttenuationFunction(vec3 ambient,vec3 diffuse,vec3 specular)
{
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;   

    return  (ambient + diffuse + specular );//�����ߵķ���������һ��õ����յľ���ģ��
}
