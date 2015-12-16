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

uniform sampler2D u_shadowMap;
uniform float time;
uniform vec2 u_iScreenSize;
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
	o_color = vec4(v_position.z / gl_DepthRange.far);
}