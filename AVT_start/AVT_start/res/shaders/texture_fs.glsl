#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

out vec4 FragmentColor;

uniform sampler2D u_Texture;

void main(void)
{
	vec4 texColor = texture(u_Texture, exTexcoord);
	FragmentColor = texColor;
}
