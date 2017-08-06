#version 410
out vec4 FragColor;
in vec2 Texcoord;
in vec3 Color;

uniform sampler2D myTextureSampler;

void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
 FragColor = texture( myTextureSampler, Texcoord ).rgba;
} 