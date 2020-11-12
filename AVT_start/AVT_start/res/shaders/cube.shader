#shader vertex
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexcoord;
layout(location = 2) in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

uniform mat4 ModelMatrix;
uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	exPosition = inPosition;
	exTexcoord = inTexcoord;
	exNormal = inNormal;

	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}

#shader fragment
#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

out vec4 FragmentColor;

void main(void)
{
/** /
//	vec3 color = vec3(1.0);
//	vec3 color = (normalize(exPosition) + vec3(1.0)) * 0.5;
//	vec3 color = vec3(exTexcoord, 0.0);
//	vec3 color = (exNormal + vec3(1.0)) * 0.5;
	FragmentColor = vec4(color,1.0);
/**/
	vec3 N = normalize(exNormal);
	vec3 direction = vec3(1.0, 0.5, 0.25);
	float intensity = max(dot(direction, N), 0.0);
	FragmentColor = vec4(vec3(intensity), 1.0);
/**/
}
