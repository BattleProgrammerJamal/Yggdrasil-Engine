#version 330

layout(location=0) in vec3 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec2 a_uv;

uniform mat4 u_world;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_uv;

void main(void)
{
	v_position = a_position;
	v_normal = a_normal;
	v_uv = a_uv;

	gl_Position = u_proj * u_view * u_world * vec4(a_position, 1.0);
}