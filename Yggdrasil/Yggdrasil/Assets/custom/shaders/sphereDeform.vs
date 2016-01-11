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
	mat4 world;
};

uniform float time;

void main(void)
{
	v_position = a_position;
	v_normal = a_normal;
	v_tangent = a_tangent;
	v_uv = a_uv;
	vec4 pos = vec4(a_position, 1.0);
	float dt = time / 1000.0;
	
	float pi = 4.0 * atan(1.0);
	
	float x = gl_InstanceID / 16.0,
		y = mod(gl_InstanceID, 16.0);
		
	float 	U = 2.0 * pi * x / 32,
			V = 3.0 * pi * y / 32;
			
	pos.x = pos.x + 15.0 * cos(0.5 - dt * U) * sin(V);
	pos.y = pos.y + 10.0 * cos(0.5 - U) * sin(1.0 - dt * V);
	pos.z = pos.z + 20.0 * cos(0.5 - U) * sin(1.0 - dt * V * cos(-V * U));
	
	/*
	pos.x = pos.x + 8.0 * gl_InstanceID + cos(dt * pos.y);
	pos.y = pos.y + 20.0 * gl_InstanceID + cos(dt * pos.x);
	pos.z = pos.z + 9.0 * gl_InstanceID + sin(dt * pos.z);
	*/
	
	gl_Position = proj * view * world * pos;
}