#version 430

#define MAXIMUM_LIGHT 16

struct MaterialDefault
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	float ka;
	float kd;
	float ks;
};

struct Light
{
	vec3 position;
	vec3 reflectance;
	float intensity;
};

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

uniform sampler2D u_shadowMap;
uniform sampler2D u_texture0;
uniform float time;
uniform vec2 u_iScreenSize;
uniform MaterialDefault u_material;
uniform Light u_lights[MAXIMUM_LIGHT];
uniform int u_lightCount;
uniform vec3 u_cameraPosition;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform vec3 u_fogColor;
uniform int u_fogEnabled;

const float dmin = 0.0;
const float dmax = 20.0;

out vec4 o_color;

layout (std140, binding = 1) uniform Matrices
{
    mat4 view;
    mat4 proj;
	mat4 world;
};

void main(void)
{
	vec4 shadowMap = texture(u_shadowMap, v_uv);
	vec4 tex = texture(u_texture0, v_uv);
	float dt = time / 1000.0;	
	vec3 N = normalize(v_normal);
	vec3 V = normalize(mat3(view) * v_position);
	
	vec3 lighting = u_material.ambient * u_material.ka;
	for(int i = 0; i < u_lightCount; ++i)
	{
		vec3 L = normalize(u_lights[i].position);
		L.x += cos(i * dt);
		L.y += cos(i * 2.0 * dt);
		L.z += sin(i * 4.0 * dt);
		vec3 H = (L + V) / length(L + V);
		float NDotL = dot(N, L);
		
		vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * u_material.kd;
		float specularTerm = 0.0;
		if(NDotL > 0.0)
		{
			specularTerm = pow(dot(N, H), u_material.shininess);
		}
		vec3 specular = u_material.specular * specularTerm * u_material.ks;
		
		vec3 kl = u_lights[i].reflectance * u_lights[i].intensity;
		
		lighting += diffuse + specular;
		lighting *= kl;
	}
	
	vec4 col = tex + vec4(lighting, 1.0);
	
	float att = 0.0;
	if(u_fogEnabled == 1)
	{
		float d = length(u_cameraPosition - v_position);
		att = smoothstep(u_fogMinDistance, u_fogMaxDistance, d);
	}
	//o_color = mix(col, vec4(u_fogColor, 1.0), att);
	o_color = vec4(0.5, 0.5, 0.5, 1.0) * u_material.diffuse * dot(N, vec3(-1.5 + -4.0 * dt * -0.2, -2.0 * dt * 0.25, 2.0 * dt * -0.5)) +
	shadowMap;
}