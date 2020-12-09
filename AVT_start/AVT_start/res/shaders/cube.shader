#shader vertex
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexcoord;
layout(location = 2) in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;
out float exzbuf;

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
	exPosition = inPosition;
	exTexcoord = inTexcoord;
	exNormal = inNormal;

	if (fake == 1 && inPosition == vec3(1, -1, -1)) exzbuf = 0.02;
	else if (fake == 1 && inPosition == vec3(-1, 1, -1)) exzbuf = 0.98;
	else exzbuf = zbuf;

	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}

#shader fragment
#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;
in float exzbuf;

out vec4 FragmentColor;

void main(void)
{
	vec3 norm = normalize(exNormal);
	FragmentColor = vec4(norm, 1.0);
	if (exzbuf >= 0) {
		gl_FragDepth = exzbuf * gl_FragCoord.z;
	}
}
