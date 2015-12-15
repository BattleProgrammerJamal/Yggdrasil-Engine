#version 410

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

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

uniform sampler2D u_texture0;
uniform vec2 u_texture_repeat0;
uniform float time;
uniform vec2 u_iScreenSize;
uniform MaterialDefault u_material;

out vec4 o_color;

//layout (std140, binding = 1) uniform Matrices
layout (std140) uniform Matrices
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

uniform mat4 u_view;
uniform mat4 u_proj;

void main(void)
{
	vec2 uv = vec2(v_uv.x * u_texture_repeat0.x, v_uv.y * u_texture_repeat0.y);
	vec4 tex = texture(u_texture0, v_uv);
	float dt = time / 1000.0;	
	vec3 N = normalize(v_normal);
	vec3 L = normalize(vec3(0.0, 0.0, 1.0));
	//vec3 V = normalize(mat3(view) * v_position);
	vec3 V = normalize(mat3(u_view) * v_position);
	vec3 H = (L + V) / length(L + V);
	float NDotL = dot(N, L);
	
	vec3 ambient = u_material.ambient * u_material.ka;
	vec3 diffuse = u_material.diffuse * max(NDotL, 0.0) * u_material.kd;
	float specularTerm = 0.0;
	if(NDotL > 0.0)
	{
		specularTerm = pow(dot(N, H), u_material.shininess);
	}
	vec3 specular = u_material.specular * specularTerm * u_material.ks;
	vec3 lighting = ambient + diffuse + specular;
	
    o_color = tex * vec4(lighting, 1.0);
}