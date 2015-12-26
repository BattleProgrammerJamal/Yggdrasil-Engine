#version 430

in vec2 v_uv;
uniform sampler2D u_sceneTexture;

out vec4 o_color;

void main(void)
{
	vec4 sceneTexture = texture(u_sceneTexture, v_uv);
	o_color = sceneTexture;
}