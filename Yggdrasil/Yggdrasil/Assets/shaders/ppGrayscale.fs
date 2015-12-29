#version 430

in vec2 v_uv;
uniform sampler2D u_sceneTexture;

out vec4 o_color;

float lumi(vec4 color)
{
	float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
	return average;
}

void main(void)
{
	vec4 sceneTexture = texture(u_sceneTexture, v_uv);
	o_color = vec4(vec3(lumi(sceneTexture)), 1.0);
}