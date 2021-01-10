#version 330 core

layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexcoord;
layout(location=2) in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;
out vec3 view_pos;

uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
layout(std140) uniform Matrices{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	// camera position
	mat4 view = inverse(ViewMatrix);
	view_pos.x = view[3][0];
	view_pos.y = view[3][1];
	view_pos.z = view[3][2];
	
	// vertex info
	exPosition = vec4(ViewMatrix * ModelMatrix * vec4(inPosition,1)).xyz;
	exTexcoord = inTexcoord;
	exNormal = NormalMatrix * inNormal;

	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}