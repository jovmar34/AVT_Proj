#version 330 core
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexcoord;
layout(location=2) in vec3 inNormal;

out vec2 exTexcoord;

layout(std140) uniform Matrices{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main() 
{
	exTexcoord = inTexcoord;
    gl_Position = vec4(inPosition.xy, 0.0, 1.0);

}