#version 410

struct MaterialDefault
{
	vec3 ambient;
	float ka;
};

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

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
	vec4 tex = texture(u_texture0, v_uv);
	o_color = tex + vec4(u_material.ambient * u_material.ka, 1.0);
}