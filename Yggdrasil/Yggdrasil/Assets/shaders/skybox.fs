#version 430

in vec3 v_position;

out vec4 o_color;

uniform samplerCube u_skybox;

layout (std140, binding = 1) uniform Matrices
{
    mat4 view;
    mat4 proj;
	mat4 world;
};

void main(void)
{
	vec3 uv = vec3(v_position);
	vec4 skybox = texture(u_skybox, uv);
    o_color = skybox;
}