#version 410
layout(location = 0) in vec2 location;

in vec3 color;
in vec2 texcoord;
out vec3 Color;
out vec2 Texcoord;

uniform mat4 uProjectionMatrix;

void main()
{
	gl_Position = uProjectionMatrix * vec4(location.x, location.y, 0, 1.0);
	Texcoord = texcoord;
	Color = vec3(1.0f, 0.5f, 0.2f);
}