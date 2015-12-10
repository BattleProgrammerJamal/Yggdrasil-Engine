#version 430

layout(location=0) in vec3 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec2 a_uv;

layout (std140, binding = 1) uniform Matrices
{
    mat4 view;
    mat4 projection;
};

uniform mat4 u_world;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_uv;

void main(void)
{
	v_position = a_position;
	v_normal = a_normal;
	v_uv = a_uv;

	gl_Position = projection * view * u_world * vec4(a_position, 1.0);
}