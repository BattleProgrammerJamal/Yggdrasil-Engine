#version 430

layout(location=0) in vec3 a_position;

out vec3 v_position;

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
	vec4 pos = proj * view * vec4(a_position, 1.0);
	
	gl_Position = pos.xyww;
}