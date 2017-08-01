#version 410
layout(location = 0) in vec3 inCoord;
uniform mat4 uProjectionMatrix;

void main()
{
	gl_Position = uProjectionMatrix * vec4(inCoord.x, inCoord.y, 0, 1.0);
}