#version 330 core

uniform vec3 u_AlbedoColor;

out vec4 FragmentColor;

void main(void)
{
    FragmentColor = vec4(u_AlbedoColor, 0.5);
}
