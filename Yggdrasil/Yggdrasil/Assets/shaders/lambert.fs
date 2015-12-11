#version 330

in vec3 v_position;
in vec3 v_normal;
in vec2 v_uv;

out vec4 o_color;

void main(void)
{
    o_color = vec4(v_normal, 1.0);
}