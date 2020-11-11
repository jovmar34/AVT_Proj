#shader vertex
#version 330 core

layout(location = 0)in vec4 in_Position;
layout(location = 1)in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 ModelMatrix;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};


void main(void)
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	ex_Color = in_Color;
}

#shader fragment
#version 330 core

in vec4 ex_Color;
out vec4 out_Color;

void main(void)
{
	out_Color = ex_Color;
}
