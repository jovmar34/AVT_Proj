#version 330 core

layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexcoord;
layout(location=2) in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

out vec3 exColor;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec3 u_AlbedoColor;

void main(void)
{
	exPosition = inPosition;
	exTexcoord = inTexcoord;
	exNormal = inNormal;

	vec4 MCPosition = vec4(inPosition, 1.0);

	//light
	vec3 light_dir      = vec3(0, 0.5, 1);
    vec3 light_color    = vec3(0.7);
    vec3 ambient_color  = 0.2 * u_AlbedoColor; 

    //Transform to eyespace
    mat4 mv_matrix = ViewMatrix * ModelMatrix;

    //diffuse component
	vec3 mv_vertex = vec3(mv_matrix * MCPosition);
    vec3 mv_normal = vec3(mv_matrix * vec4(inNormal, 0.0));

	float diffuse = max(dot(mv_normal, light_dir), 0.1);
    vec3 diffuse_color = diffuse * u_AlbedoColor;

    //specular component
    vec3 E = normalize(-mv_vertex);
    vec3 R = normalize(-reflect(light_dir, mv_normal));

	float specular = pow(max(dot(R,E),0.0), 32.0);
    vec3 specular_color = specular * light_color;

    exColor = vec3(ambient_color + diffuse_color + specular_color);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}
