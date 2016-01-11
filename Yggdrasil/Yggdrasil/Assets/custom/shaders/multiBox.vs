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
	
	int width = 64, height = 16;
	int idx = gl_InstanceID;
	float z = float(gl_InstanceID / (width * height));
	idx -= (int(z) * width * height);
	float y = gl_InstanceID / width;
	float x = float(mod(gl_InstanceID, width));
	pos.x = pos.x + 1.0 * x;
	pos.z = pos.z + 4.0 * y;
	pos.y = pos.y + 2.0 * z;
	
	pos.y += cos(gl_InstanceID * width + dt);
	
	gl_Position = proj * view * world * pos;
}