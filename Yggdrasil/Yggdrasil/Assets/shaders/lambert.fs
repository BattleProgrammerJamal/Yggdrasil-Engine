#version 430

#define MAXIMUM_LIGHT 16

struct MaterialDefault
{
	vec3 ambient;
	vec3 diffuse;
	float ka;
	float kd;
};

struct Light
{
	vec3 position;
	vec3 reflectance;
	float intensity;
};

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

uniform sampler2D u_texture0;
uniform float time;
uniform vec2 u_iScreenSize;
uniform MaterialDefault u_material;
uniform Light u_lights[MAXIMUM_LIGHT];
uniform int u_lightCount;

out vec4 o_color;

layout (std140, binding = 1) uniform Matrices
{
    mat4 view;
    mat4 proj;
	mat4 world;
};

void main(void)
{
	vec4 tex = texture(u_texture0, v_uv);
	float dt = time / 1000.0;	
	vec3 N = normalize(v_normal);
	
	vec3 lighting = u_material.ambient * u_material.ka;
	for(int i = 0; i < u_lightCount; ++i)
	{
		vec3 L = normalize(u_lights[i].position);
		float NDotL = dot(N, L);
		
		vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * u_material.kd;
		
		lighting += (u_lights[i].intensity * u_lights[i].reflectance) + diffuse;
	}
	
    o_color = tex * vec4(lighting, 1.0);
}