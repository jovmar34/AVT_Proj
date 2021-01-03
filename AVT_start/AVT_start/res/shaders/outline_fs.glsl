#version 330 core

uniform vec4 OutlineColor = vec4(1,1,1,1);

out vec4 FragmentColor;

void main(void)
{
    FragmentColor = OutlineColor;
}
