#version 330 core

in vec2 exTexcoord;

uniform sampler2D u_Texture;

out vec4 FragmentColor;

void main(void)
{
    FragmentColor = texture(u_Texture, exTexcoord);
}
