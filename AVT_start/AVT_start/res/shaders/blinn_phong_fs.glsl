#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

in vec3 view_pos;

out vec4 FragmentColor;

uniform vec3 u_AlbedoColor;

void main(void)
{
    
    //light properties
    vec3 light_dir      = vec3(0, 0.5, 1);
    vec3 light_color    = vec3(0.7);
    vec3 ambient_color  = 0.2 * u_AlbedoColor; 

    //diffuse component
	vec3 normal         = normalize(exNormal);
    float diffuse       = max(dot(light_dir, normal), 0.0);
    vec3 diffuse_color  = diffuse * u_AlbedoColor;

    //specular
    vec3 view_dir       = normalize(view_pos - exPosition);
    vec3 halfway_dir    = normalize(light_dir + view_dir);  
    float specular      = pow(max(dot(normal, halfway_dir), 0.0), 32.0);
    vec3 specular_color = specular * light_color;

    FragmentColor = vec4(ambient_color + diffuse_color + specular_color, 1.0);
}