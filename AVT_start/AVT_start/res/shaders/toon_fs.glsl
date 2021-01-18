#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;
in vec3 view_pos;
in vec3 light_pos;

uniform vec3 u_AlbedoColor;
uniform sampler2D u_Texture;

out vec4 FragmentColor;

void main(void)
{

    // light properties
	vec3 light_dir = normalize(light_pos - exPosition);

    float light_intensity = 0.7;

    //diffuse component
	vec3 normal         = normalize(exNormal);
    float diffuse       = max(dot(light_dir, normal), 0.0) * light_intensity;

    //specular
    vec3 view_dir       = normalize(-exPosition);
    vec3 halfway_dir    = normalize(light_dir + view_dir);  
    float specular      = pow(max(dot(normal, halfway_dir), 0.0), 32.0) * light_intensity;

    float light_val = clamp(diffuse + specular, 0.0, 1.0);
    vec4 ramp_val = texture(u_Texture, vec2(0.1, 1.0 - light_val));

    FragmentColor = ramp_val * vec4(u_AlbedoColor, 1.0);
}