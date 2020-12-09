#shader vertex
#version 330 core

layout(location = 0) in vec3 inPosition;

out vec4 excol;

uniform mat4 ModelMatrix;
uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform float zbuf;
uniform int fake;

void main(void)
{
	vec4 MCPosition = vec4(inPosition, 1.0);
	excol = MCPosition;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}

#shader fragment
#version 330 core

in vec4 excol;

out vec4 FragmentColor;

void main(void)
{
	FragmentColor = excol;
}
