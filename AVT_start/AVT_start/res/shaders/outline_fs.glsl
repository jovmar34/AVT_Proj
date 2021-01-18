#version 330 core

uniform vec4 OutlineColor = vec4(0.9218,0.5820,0.2109,1);

out vec4 FragmentColor;

void main(void)
{
    FragmentColor = OutlineColor;
}
