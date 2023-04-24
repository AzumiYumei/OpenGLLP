#version 330 core
out vec4 FragColor;

struct Material {
//����ͼ���Ƶ�
    sampler2D diffuse1;
    sampler2D specular1;
    sampler2D emission1;

    //�ɾ�̬���ݿ��Ƶģ�Ŀǰ��δӦ��
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess1;
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
uniform Light light;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

vec3 PointLightFunction(PointLight light,vec3 Normal,Material material,vec3 FragPos);
vec3 DiffuseFunction(DirLight light,vec3 Normal,Material material,vec3 FragPos);
vec3 SpecularFunction(SpotLight light,vec3 Normal,Material material,vec3 FragPos);

void main()
{
    vec3 result;
    //ƽ�й�
    //vec3 lightDir = normalize(-light.direction);
    for(int i=0;i<PointLightNumber;i++)
        result += PointLightFunction( pointLights[i], Normal, material , FragPos);

    FragColor = vec4(result, 1.0);
}

vec3 PointLightFunction(PointLight light,vec3 Normal,Material material,vec3 FragPos)
{
    vec3 norm = normalize(Normal);//�����淨������

    //������
    vec3 lightDir = normalize(light.position - FragPos);//��ȡ����ָ���Դ������
    float diff = max(dot(norm, lightDir), 0.0);//���淨����������������ļнǵ�ֵdiff�����С��0����Ϊ0
    
    //���淴��
    vec3 viewDir = normalize(cameraPos - FragPos);//��������ָ�������������
    vec3 reflectDir = reflect(-lightDir, norm);  //����Դָ������������뷨�߷���һ����㷴�������
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//����߹��С


    //�����������ɫ��һ����������ɫһ�£�������diff��������ͼ��rgb��ɫ���õ�������
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    // ������,ʹ����ͼ��rgb���㻷����
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    //����������ɫ��һ�����Դ��ɫһ�£������ڸ߹��С��������ͼ��rgb��ɫ���õ����淴��
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    //˥��
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;   
    //�����ߵķ���������һ��õ����յľ���ģ��
    vec3 result=ambient + diffuse + specular;
        
    return result;
}

