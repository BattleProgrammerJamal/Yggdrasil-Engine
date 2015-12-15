#version 410

layout(location=0) in vec3 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec3 a_tangent;
layout(location=3) in vec2 a_uv;

out vec3 v_position;
out vec3 v_normal;
out vec3 v_tangent;
out vec2 v_uv;
out mat4 v_world;

//layout (std140, binding = 1) uniform Matrices
layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

uniform mat4 u_view;
uniform mat4 u_proj;

uniform mat4 u_translation;
uniform mat4 u_rotationX;
uniform mat4 u_rotationY;
uniform mat4 u_rotationZ;
uniform mat4 u_scale;
uniform mat4 u_world;
uniform float time;

void main(void)
{
	v_position = a_position;
	v_normal = a_normal;
	v_tangent = a_tangent;
	v_uv = a_uv;
	mat4 world = u_scale * (u_rotationX * u_rotationY * u_rotationZ) * u_translation;
	vec4 pos = vec4(a_position, 1.0);
	
	gl_Position = u_proj * u_view * world * pos;
	
	v_world = world;
}