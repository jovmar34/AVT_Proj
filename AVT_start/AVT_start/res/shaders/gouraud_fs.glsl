#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

in vec3 exColor;

out vec4 FragmentColor;

void main(void)
{
    FragmentColor = vec4(exColor, 1.0);
}

