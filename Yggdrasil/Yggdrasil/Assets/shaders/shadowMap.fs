#version 430

#define MAXIMUM_LIGHT 16

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

uniform float time;
uniform vec2 u_iScreenSize;
uniform Light u_lights[MAXIMUM_LIGHT];
uniform int u_lightCount;

layout (std140, binding = 1) uniform Matrices
{
    mat4 view;
    mat4 proj;
	mat4 world;
};

out vec4 o_color;

void main(void)
{
	o_color = vec4(vec3(gl_FragCoord.z), 0.0);
}