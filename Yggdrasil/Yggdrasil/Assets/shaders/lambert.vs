#version 430

layout(location=0) in vec3 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec3 a_tangent;
layout(location=3) in vec2 a_uv;

out vec3 v_position;
out vec3 v_normal;
out vec3 v_tangent;
out vec2 v_uv;

layout (std140, binding = 1) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

uniform mat4 u_translation;
uniform mat4 u_rotationX;
uniform mat4 u_rotationY;
uniform mat4 u_rotationZ;
uniform mat4 u_scale;
uniform float time;

void main(void)
{
	v_position = a_position;
	v_normal = a_normal;
	v_tangent = a_tangent;
	v_uv = a_uv;
	mat4 world = u_scale * (u_rotationZ * u_rotationY * u_rotationX) * u_translation;
	vec4 pos = vec4(a_position, 1.0);
	pos.x = pos.x + -0.25 + 2.0 * sin(time / 1000.0) * cos(gl_InstanceID);
	pos.y = pos.y + -0.5 + cos(time / 1000.0) * sin(gl_InstanceID);
	pos.z = pos.z + 0.75 + cos(time / 1000.0) * sin(gl_InstanceID);
	
	gl_Position = proj * view * world * pos;
}