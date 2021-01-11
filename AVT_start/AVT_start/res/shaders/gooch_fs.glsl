#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;
in vec3 view_pos;
in vec3 light_pos;

uniform float u_WarmDifuse = 0.3;
uniform vec3 u_WarmColor = vec3(0.78, 0.78, 0.42);

uniform float u_ColdDifuse = 0.3;
uniform vec3 u_ColdColor = vec3(0.24, 0.24, 0.69);

uniform vec3 u_AlbedoColor;

out vec4 FragmentColor;

void main(void)
{
    // light properties
	vec3 light_dir = normalize(light_pos - exPosition);

    //diffuse component
	vec3 normal         = normalize(exNormal);
    float diffuse       = max(dot(light_dir, normal), 0.0);

    vec3 warm = min(u_WarmColor + u_WarmDifuse * u_AlbedoColor, 1.0);
    vec3 cold = min(u_ColdColor + u_ColdDifuse * u_AlbedoColor, 1.0);
    vec3 diffuse_color = mix(warm, cold, diffuse);

    //specular
    vec3 view_dir           = normalize(-exPosition);
    vec3 halfway_dir        = normalize(light_dir + view_dir);  
    float specular_color    = pow(max(dot(normal, halfway_dir), 0.0), 32.0);

    FragmentColor =  vec4(min(diffuse_color + specular_color, 1.0), 1.0);
}
