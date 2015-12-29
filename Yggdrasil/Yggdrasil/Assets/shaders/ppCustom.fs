#version 430

in vec2 v_position;
in vec2 v_uv;
uniform sampler2D u_sceneTexture;

out vec4 o_color;

const float offset = 1.0 / 300;

uniform float time;

void main(void)
{
	float dt = time / 1000.0;
	vec4 sceneTexture = texture(u_sceneTexture, v_uv);
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2(0.0f,    offset),
		vec2(offset,  offset),
		vec2(-offset, 0.0f),
		vec2(0.0f,    0.0f),
		vec2(offset,  0.0f),
		vec2(-offset, -offset),
		vec2(0.0f,    -offset),
		vec2(offset,  -offset)  
	);

    float kernel[9] = float[](
		-1, -1, -1,
		-1 * cos(dt),  9, -1,
		-1, -1, -1 * sin(dt)
    );
	
	vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
		sampleTex[i] = vec3(texture(u_sceneTexture, v_uv.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
	{
        col += sampleTex[i] * kernel[i];
	}
	
	float d = length(0.2 * mod(vec4(col, 1.0), cos(dt * dot(v_position, v_uv))));
	col.r = col.r * sqrt(1.0/d) * sin(d);
	col.g = col.g * sin(d);
	col.b = col.b * cos(d);
	o_color = vec4(col, 1.0);
}