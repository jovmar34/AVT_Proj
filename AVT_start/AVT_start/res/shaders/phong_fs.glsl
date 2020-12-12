#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

out vec4 FragmentColor;

uniform vec3 u_AlbedoColor;

void main(void)
{
	vec3 N = normalize(exNormal);
	vec3 direction = vec3(1.0, 0.5, 0.25);
	float intensity = max(dot(direction, N), 0.0);
	FragmentColor = vec4(vec3(intensity), 1.0) * vec4(u_AlbedoColor, 1.0);
}
