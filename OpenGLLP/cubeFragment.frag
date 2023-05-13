#version 330 core
out vec4 FragColor;

struct Material {
//ÓÉÌùÍ¼¿ØÖÆµÄ
    sampler2D diffuse;
}; 

uniform Material material;

in vec2 TexCoords;

void main()
{             
    vec4 texColor = texture(material.diffuse, TexCoords);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}