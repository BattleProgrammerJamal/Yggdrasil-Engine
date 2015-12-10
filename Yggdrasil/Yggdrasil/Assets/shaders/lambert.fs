#version 430
precision highp float;

layout (std140, binding = 1) uniform Matrices
{
    mat4 view;
    mat4 projection;
};

in vec3 v_position;
in vec3 v_normal;
in vec2 v_uv;

out vec4 o_color;

void main(void)
{
    o_color = vec4(v_normal, 1.0);
}