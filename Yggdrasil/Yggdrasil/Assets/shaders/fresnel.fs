#version 430

#define MAXIMUM_LIGHT 16

struct MaterialDefault
{
	vec3 color;
	float roughness;
	int operation;
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
	vec3 V = normalize(mat3(view) * v_position);
	
	float kf = pow(1.0 - dot(N, normalize(V)), u_material.roughness);
	vec4 fresnel = vec4(vec3(kf), 1.0);
	
	if(u_material.operation == 0)
	{
		o_color = tex + vec4(u_material.color, 1.0) + fresnel;
	}
	else
	{
		if(u_material.operation == 1)
		{
			o_color = tex + vec4(u_material.color, 1.0) - fresnel;
		}
		else
		{
			o_color = tex + vec4(u_material.color, 1.0) * fresnel;
		}
	}
}