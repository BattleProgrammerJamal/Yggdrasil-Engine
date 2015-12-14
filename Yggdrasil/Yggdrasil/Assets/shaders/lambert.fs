#version 430

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

uniform sampler2D u_texture0;
uniform vec2 u_texture_repeat0;
uniform float time;
uniform vec2 u_iScreenSize;

out vec4 o_color;

layout (std140, binding = 1) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

struct Light
{
	vec3 position;
	vec3 reflectance;
	float intensity;
};

Light makeLight(vec3 position, vec3 reflectance, float intensity)
{
	Light l;
	l.position = position;
	l.reflectance = reflectance;
	l.intensity = intensity;
	return l;
}

void main(void)
{
	vec2 uv = vec2(v_uv.x * u_texture_repeat0.x, v_uv.y * u_texture_repeat0.y);
	vec4 tex = texture(u_texture0, v_uv);
	float dt = time / 1000.0;	
	vec3 N = normalize(v_normal);
	Light LIGHTS[] = Light[](
		makeLight(normalize(vec3(0.0, 0.0, 1.0)), vec3(1.0, 0.0, 0.0), 80.0),
		makeLight(normalize(vec3(0.0, 0.0, -1.0)), vec3(0.0, 1.0, 0.0), 40.0),
		makeLight(normalize(vec3(0.0, 1.0, 0.0)), vec3(0.0, 0.0, 1.0), 20.0),
		makeLight(normalize(vec3(0.0, -1.0, 0.0)), vec3(0.45, 0.0, 1.0), 30.0),
		makeLight(normalize(vec3(-1.0, 1.0, 1.0)), vec3(0.7, 0.5, 0.3), 100.0)
	);
	vec3 V = mat3(view) * v_position;
	
	vec3 ambient = vec3(1.0, 1.0, 1.0) * 0.4;
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);
	for(int i = 0; i < LIGHTS.length(); ++i)
	{
		LIGHTS[i].position += cos(dt * i) * 0.5;
	
		vec3 H = normalize((LIGHTS[i].position + V) / 2.0);
		float NDotL = dot(N, LIGHTS[i].position);
		diffuse += LIGHTS[i].reflectance * max(NDotL, 0.0) * 1.0;
		float specularTerm = 0.0;
		if(NDotL > 0.0)
		{
			specularTerm = pow(dot(N, H), LIGHTS[i].intensity);
		}
		specular += LIGHTS[i].reflectance * specularTerm * 1.0;
	}
	vec3 lighting = ambient * diffuse + specular;
	
	float l = (tex.r + tex.g + tex.b) / 3.0;
	if(l > 0.7)
	{
		tex.g = tex.r * cos(dt * l * tex.b);
		tex.b = tex.g * cos(dt * l * tex.r);
	}
	
    o_color = tex + vec4(lighting, 1.0);
}