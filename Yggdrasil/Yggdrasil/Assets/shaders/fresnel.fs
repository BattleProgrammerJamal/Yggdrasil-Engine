#version 410

struct MaterialDefault
{
	vec3 color;
	float roughness;
	int operation;
};

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;
in mat4 v_world;

uniform sampler2D u_texture0;
uniform vec2 u_texture_repeat0;
uniform float time;
uniform vec2 u_iScreenSize;
uniform MaterialDefault u_material;

out vec4 o_color;

//layout (std140, binding = 1) uniform Matrices
layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

uniform mat4 u_view;
uniform mat4 u_proj;

void main(void)
{
	vec3 N = normalize(v_normal);
	vec3 L = normalize(vec3(0.0, 0.0, 1.0));
	//vec3 V = normalize(mat3(view) * v_position);
	vec3 V = normalize((v_world * vec4(v_position, 1.0)).xyz - (u_view * vec4(v_position, 1.0)).xyz);
	vec4 tex = texture(u_texture0, v_uv);
	
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