#version 330 core
out vec4 FragColor;

struct Material {
//����ͼ���Ƶ�
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
    //ƽ�й�
    result = CalcDirLight(dirLight, Normal, cameraPos);
    for(int i=0;i<PointLightNumber;i++)
        result += PointLightFunction( pointLights[i], Normal, material , FragPos);
    
    FragColor = vec4(result, 1.0);
}

vec3 PointLightFunction(PointLight light,vec3 Normal,Material material,vec3 FragPos)
{
    vec3 norm;//�����淨������
    if(useNormal)
    {
        norm = texture(material.normal,TexCoords).rgb;
        // ����������ת��Ϊ��Χ[-1,1]
        norm = normalize(norm * 2.0 - 1.0);
        norm = normalize(TBN * norm);
    }
    else
    {
        norm = normalize(Normal);//�����淨������
    }

    //������
    vec3 lightDir = normalize(light.position - FragPos);//��ȡ����ָ���Դ������
    float diff = max(dot(norm, lightDir), 0.0);//���淨����������������ļнǵ�ֵdiff�����С��0����Ϊ0
    
    //���淴��
    vec3 viewDir = normalize(cameraPos - FragPos);//��������ָ�������������
    float spec;
    if(isBlinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    }
    else
    {
        vec3 reflectDir = reflect(-lightDir, norm);  //����Դָ������������뷨�߷���һ����㷴�������
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//����߹��С
    }

    //�����������ɫ��һ����������ɫһ�£�������diff��������ͼ��rgb��ɫ���õ�������
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    // ������,ʹ����ͼ��rgb���㻷����
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    //����������ɫ��һ�����Դ��ɫһ�£������ڸ߹��С��������ͼ��rgb��ɫ���õ����淴��
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).r;

    //�Է���
    vec3 emission = light.emission * texture(material.emission,TexCoords).rgb;

    //˥��
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;
    
    //�����ߵķ���������һ��õ����յľ���ģ��
    vec3 result=ambient + diffuse + specular + emission;
        
    return result;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 cameraPos)
{
    vec3 lightDir = normalize(-light.direction);
    // ��������ɫ
    float diff = max(dot(normal, lightDir), 0.0);
    // �������ɫ
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(cameraPos, reflectDir), 0.0), material.shininess);
    // �ϲ����
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}
