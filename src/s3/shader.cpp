#include "s3/shader.hpp"

#include <glm/glm.hpp>

#include <stdexcept>

#include <s3/color.hpp>
#include <s3/uniformstruct.hpp>

namespace s3 {

static const char* vs_default = R"shader(
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 norm;
layout(location = 3) in vec3 tangent;

out vec3 posV;
out vec2 uvV;
out vec3 normV;
out mat3 TBN;
out mat3 iTBN;

uniform mat4 model;
uniform mat3 norm_model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(pos, 1.0);

	vec3 T = normalize(norm_model * tangent);
	vec3 N = normalize(norm_model * norm);
	// gram-schmidt orthogonalize
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);
	// handedness
	if (dot(cross(N, T), B) < 0.0) {
		T *= -1.0;
	}
	TBN = mat3(T, B, N);
	iTBN = transpose(TBN);

	posV = vec3(model * vec4(pos, 1.0));
	uvV = uv;
	normV = normalize(norm_model * norm);
}
)shader";

static const char* fs_default = R"shader(
#version 330 core

in vec3 posV;
in vec2 uvV;
in vec3 normV;
in mat3 TBN;
in mat3 iTBN;

out vec4 color;

uniform sampler2D tex;
uniform vec3 cam;

struct Material {
	sampler2D diffuse; // texture
	sampler2D specular; // specular mapping
	sampler2D emission; // optional emission mapping

	sampler2D height; // height map
	float height_scale; // height map scale

	bool normalSet; // is the normal map set?
	sampler2D normal; // optional normal mapping
	float shininess;
};
uniform Material material;

// max of each type of light
#define MAX_LIGHTS 16

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
uniform PointLight pointlights[MAX_LIGHTS];
uniform int pointLightCount;

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirlights[MAX_LIGHTS];
uniform int dirLightCount;

struct SpotLight {
	vec3 position;
	vec3 direction;
	float innerAngle;
	float outerAngle;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
uniform SpotLight spotlights[MAX_LIGHTS];
uniform int spotLightCount;

vec3 PointLightCalc(PointLight light, vec3 camDir, vec3 fragNormal, vec2 uv);
vec3 DirLightCalc(DirLight light, vec3 camDir, vec3 fragNormal, vec2 uv);
vec3 SpotLightCalc(SpotLight light, vec3 camDir, vec3 fragNormal, vec2 uv);

vec2 ParallaxMapping(vec2 uv, vec3 camDir);

void main() {
	vec3 camDir = normalize(cam - posV);
	// parallax fix
	vec2 uvP = ParallaxMapping(uvV, iTBN * camDir);
	uvP.x = clamp(uvP.x, 0.0, 1.0);
	uvP.y = clamp(uvP.y, 0.0, 1.0);

	// per-fragment normal for normal mapping purposes
	vec3 fragNormal = texture(material.normal, uvP).rgb;
	if (material.normalSet) {
		// normalizes from 0 - 1 to -1 - 1
		fragNormal = fragNormal * 2.0 - 1.0;
		fragNormal = normalize(TBN * fragNormal);
	} else {
		// just use vertex normal if no normal map is set
		fragNormal = normV;
	}

	vec3 lightSum = vec3(0.0);
	for(int i = 0; i < pointLightCount; ++i) {
		lightSum += PointLightCalc(pointlights[i], camDir, fragNormal, uvP);
	}
	for(int i = 0; i < dirLightCount; ++i) {
		lightSum += DirLightCalc(dirlights[i], camDir, fragNormal, uvP);
	}
	for(int i = 0; i < spotLightCount; ++i) {
		lightSum += SpotLightCalc(spotlights[i], camDir, fragNormal, uvP);
	}

	color = vec4(lightSum, 1.0);
}

vec3 PointLightCalc(PointLight light, vec3 camDir, vec3 fragNormal, vec2 uv) {
	vec3 lightDir = normalize(light.position - posV);
	vec3 halfDir = normalize(lightDir + camDir);

	float diff = max(dot(fragNormal, lightDir), 0.0);
	float spec = pow(max(dot(fragNormal, halfDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * texture(material.diffuse, uv).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, uv).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, uv).rgb;

	float dist = length(light.position - posV);
	float falloff = 1.0 / (light.constant + 
			light.linear * dist + 
			light.quadratic * (dist * dist)
	);

	ambient *= falloff;
	diffuse *= falloff;
	specular *= falloff;

	vec3 emission = texture(material.emission, uv).rgb;

	return ambient + diffuse + specular + emission;
}

vec3 DirLightCalc(DirLight light, vec3 camDir, vec3 fragNormal, vec2 uv) {
	vec3 lightDir = normalize(-light.direction);
	vec3 halfDir = normalize(lightDir + camDir);

	float diff = max(dot(fragNormal, lightDir), 0.0);
	float spec = pow(max(dot(fragNormal, halfDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * texture(material.diffuse, uv).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, uv).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, uv).rgb;

	vec3 emission = texture(material.emission, uv).rgb;

	return ambient + diffuse + specular + emission;
}

vec3 SpotLightCalc(SpotLight light, vec3 camDir, vec3 fragNormal, vec2 uv) {
	vec3 lightDir = normalize(light.position - posV);
	vec3 halfDir = normalize(lightDir + camDir);

	vec3 ambient = light.ambient * texture(material.diffuse, uv).rgb;
	float dist = length(light.position - posV);
	float falloff = 1.0 / (light.constant + 
			light.linear * dist + 
			light.quadratic * (dist * dist)
	);
	ambient *= falloff;

	vec3 emission = texture(material.emission, uv).rgb;

	float theta = dot(lightDir, normalize(-light.direction));
	if (theta > light.outerAngle) {
		float diff = max(dot(fragNormal, lightDir), 0.0);
		float spec = pow(max(dot(fragNormal, halfDir), 0.0), material.shininess);

		vec3 diffuse = light.diffuse * diff * texture(material.diffuse, uv).rgb;
		vec3 specular = light.specular * spec * texture(material.specular, uv).rgb;

		float epsilon = light.innerAngle - light.outerAngle;
		float intensity = clamp((theta - light.outerAngle) / epsilon, 0.0, 1.0);

		diffuse *= falloff * intensity;
		specular *= falloff * intensity;

		return ambient + diffuse + specular + emission;
	} else {
		return ambient + emission;
	}
}

vec2 ParallaxMapping(vec2 uv, vec3 camDir) {
	const float layerCt = 10;
	const float layerDepth = 1.0 / layerCt;

	vec2 duv = camDir.xy * material.height_scale / (camDir.z * layerCt);

	float curLayerHeight = 0.0;
	vec2 curUv = uv;
	float curHeightValue = texture(material.height, curUv).r;
	while (curLayerHeight < curHeightValue) {
		curUv -= duv;
		curHeightValue = texture(material.height, curUv).r;
		curLayerHeight += layerDepth;
	}

	vec2 prevUv = curUv + duv;

	float afterHeight = curHeightValue - curLayerHeight;
	float beforeHeight = texture(material.height, prevUv).r - curLayerHeight + layerDepth;

	float weight = afterHeight / (afterHeight - beforeHeight);
	vec2 finalUv = prevUv * weight + curUv * (1.0 - weight);

	return finalUv;
}

)shader";

//////////////////////// SHADER UNIFORM TEMPLATES /////////////////////////////

template <>
void shader::set_uniform(const char* name, const uniformstruct& data) {
	data.populate(name, *this);
}

template <>
void shader::set_uniform(const char* name, const glm::mat4& data) {
	int loc = glGetUniformLocation(m_prog, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &data[0][0]);
}

template <>
void shader::set_uniform(const char* name, const glm::mat3& data) {
	int loc = glGetUniformLocation(m_prog, name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, &data[0][0]);
}

template <>
void shader::set_uniform(const char* name, const glm::vec4& data) {
	int loc = glGetUniformLocation(m_prog, name);
	glUniform4fv(loc, 1, &data[0]);
}

template <>
void shader::set_uniform(const char* name, const glm::vec3& data) {
	int loc = glGetUniformLocation(m_prog, name);
	glUniform3fv(loc, 1, &data[0]);
}

template <>
void shader::set_uniform(const char* name, const color& data) {
	set_uniform<glm::vec4>(name, data);
}

template <>
void shader::set_uniform(const char* name, const GLfloat& data) {
	int loc = glGetUniformLocation(m_prog, name);
	glUniform1fv(loc, 1, &data);
}

template <>
void shader::set_uniform(const char* name, const GLint& data) {
	int loc = glGetUniformLocation(m_prog, name);
	glUniform1iv(loc, 1, &data);
}

template <>
void shader::set_uniform(const char* name, const bool& data) {
	set_uniform<GLint>(name, (int)data);
}

///////////////////////////////////////////////////////////////////////////////

shader::shader(const char* vs, const char* fs)
	: m_vs(vs),
	  m_fs(fs),
	  m_prog(0) {
	if (m_vs == nullptr && m_fs == nullptr) {
		m_vs = vs_default;
		m_fs = fs_default;
	}
	compile();
}

shader::shader()
	: m_vs(vs_default),
	  m_fs(fs_default),
	  m_prog(0) {
	compile();
}

shader::shader(shader&& other) noexcept
	: m_vs(other.m_vs),
	  m_fs(other.m_fs),
	  m_prog(other.m_prog) {
	other.m_vs	 = nullptr;
	other.m_fs	 = nullptr;
	other.m_prog = 0;
}

shader::~shader() {
	if (m_prog != 0) {
		glDeleteProgram(m_prog);
	}
}

void shader::compile() {
	if (m_prog != 0) glDeleteProgram(m_prog);

	GLuint vs, fs;
	int success;
	char infolog[512];

	vs	   = glCreateShader(GL_VERTEX_SHADER);
	fs	   = glCreateShader(GL_FRAGMENT_SHADER);
	m_prog = glCreateProgram();

	glShaderSource(vs, 1, &m_vs, nullptr);
	glShaderSource(fs, 1, &m_fs, nullptr);

	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 512, nullptr, infolog);
		throw std::runtime_error("vertex shader error!\n" + std::string(infolog));
	}

	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fs, 512, nullptr, infolog);
		throw std::runtime_error("fragment shader error!\n" + std::string(infolog));
	}

	glAttachShader(m_prog, vs);
	glAttachShader(m_prog, fs);
	glLinkProgram(m_prog);
	glGetProgramiv(m_prog, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_prog, 512, NULL, infolog);
		throw std::runtime_error("program link error!\n" + std::string(infolog));
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void shader::use() {
	glUseProgram(m_prog);
}

unsigned int shader::id() const {
	return m_prog;
}

}
