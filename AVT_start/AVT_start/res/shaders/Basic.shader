#shader vertex
#version 330 core

in vec4 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 Matrix;

void main(void)
{
	gl_Position = Matrix * in_Position;
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
