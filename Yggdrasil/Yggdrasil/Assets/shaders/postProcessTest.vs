#version 430

layout(location=0) in vec2 a_position;
layout(location=1) in vec2 a_uv;

out vec2 v_position;
out vec2 v_uv;

void main(void)
{
	gl_Position = vec4(a_position, 0.0, 1.0);
	v_position = a_position;
	v_uv = a_uv;
}