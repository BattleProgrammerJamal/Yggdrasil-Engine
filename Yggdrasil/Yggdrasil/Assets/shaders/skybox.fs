#version 430

in vec3 v_position;

out vec4 o_color;

uniform samplerCube u_skybox;
uniform sampler2D u_cloud;

layout (std140, binding = 1) uniform Matrices
{
    mat4 view;
    mat4 proj;
	mat4 world;
};

uniform float time;

void main(void)
{
	float dt = time / 1000.0;
	vec3 uv = vec3(v_position);
	vec4 cloud = texture(u_cloud, uv.xy);
	vec4 skybox = texture(u_skybox, uv);
	
	o_color = cloud + skybox;
}