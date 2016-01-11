#version 430

#define MAXIMUM_LIGHT 16

#define BLINN_APPROXIMATION 1

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
	vec3 direction;
	vec3 reflectance;
	float intensity;
	int type;
	float constantAttenuation;
	float linearAttenuation;
	float exponentialAttenuation;
};

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

uniform sampler2D u_shadowMap;
uniform mat4 u_depthBiasWVP;
uniform sampler2D u_texture0;
uniform vec2 u_texture_repeat;
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
uniform samplerCube u_skybox;

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
	vec4 shadowMapUVS = u_depthBiasWVP * (world * vec4(v_position, 1.0));
	vec4 shadowMap = texture(u_shadowMap, shadowMapUVS.xy);
	vec4 tex = texture(u_texture0, vec2(v_uv.x, -v_uv.y));
	float dt = time / 1000.0;	
	vec3 N = normalize(v_normal);
	vec3 V = normalize(mat3(view) * v_position);
	float ratio = 1.0 / 1.33;
	
	vec3 lighting = u_material.ambient * u_material.ka;
	for(int i = 0; i < u_lightCount; ++i)
	{
		vec3 L = normalize(u_lights[i].position);
		float NDotL = dot(N, L);
		
		vec3 position = vec3(world * vec4(v_position, 1.0));
		vec3 I = normalize(position - u_cameraPosition);
		vec3 R = reflect(I, N);
		vec3 Re = refract(I, N, ratio);
		
		vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * u_material.kd;
		
		vec3 specular = vec3(0.0);
		if(BLINN_APPROXIMATION == 1)
		{
			vec3 H = (L + V) / length(L + V);
			float specularTerm = 0.0;
			if(NDotL > 0.0)
			{
				specularTerm = pow(dot(N, H), u_material.shininess);
			}
			specular = u_material.specular * specularTerm * u_material.ks;
		}
		else
		{
			float specularTerm = 0.0;
			if(NDotL > 0.0)
			{
				specularTerm = pow(dot(R, V), u_material.shininess);
			}
			specular = u_material.specular * specularTerm * u_material.ks;
		}
		
		vec3 skyboxReflection = texture(u_skybox, R).xyz;
		vec3 skyboxRefraction = texture(u_skybox, Re).xyz;
		
		vec3 kl = u_lights[i].reflectance * u_lights[i].intensity;
		
		specular *= skyboxReflection;
		specular *= skyboxRefraction;
		
		lighting += diffuse + specular;
		lighting *= kl;
		
		if(u_lights[i].type == 1)
		{
			float dst = length(vec3(world * vec4(v_position, 1.0)) - u_lights[i].position);
			float att = 1.0 / (u_lights[i].constantAttenuation + u_lights[i].linearAttenuation * dst + u_lights[i].exponentialAttenuation * dst * dst);
			lighting *= att;
		}
	}
	
	vec4 col = tex + vec4(lighting, 1.0);
	
	float att = 0.0;
	if(u_fogEnabled == 1)
	{
		float d = length(u_cameraPosition - v_position);
		att = smoothstep(u_fogMinDistance, u_fogMaxDistance, d);
	}
	
	vec4 wPos = world * vec4(v_position, 1.0);
	float zDepth = wPos.z / wPos.w; 
	
	float bias = 0.5, visibility = 1.0;
	if(shadowMap.z > shadowMapUVS.z - bias)
	{
		visibility = 0.5;
	}
	
	o_color = visibility * mix(col, vec4(u_fogColor, 1.0), att);
}