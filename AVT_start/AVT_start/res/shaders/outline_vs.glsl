#version 330 core

layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexcoord;
layout(location=2) in vec3 inNormal;

uniform mat4 ModelMatrix;
layout(std140) uniform Matrices{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform float OutlineWidth = 0.04;

void main(void)
{
	vec4 MCPosition = vec4(inPosition, 1.0);
	vec4 pos = MCPosition + vec4(inNormal,0) * OutlineWidth;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * pos;
}