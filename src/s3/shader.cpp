#include "s3/shader.hpp"

#include <glm/glm.hpp>
#include <stdexcept>

namespace s3 {

static const char* vs_default = R"shader(
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 norm;

out vec3 posV;
out vec2 uvV;
out vec3 normV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(pos, 1.0);

	posV = pos;
	uvV = uv;
	normV = norm;
}
)shader";

static const char* fs_default = R"shader(
#version 330 core

in vec3 posV;
in vec2 uvV;
in vec3 normV;

out vec4 color;

uniform sampler2D tex;

void main() {
	color = texture(tex, uvV);
}
)shader";

template <>
void shader::set_uniform(const char* name, const glm::mat4&& data) {
	int loc = glGetUniformLocation(m_prog, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &data[0][0]);
}

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

void shader::del() {
	glDeleteProgram(m_prog);
}

void shader::compile() {
	if (m_prog != 0) del();

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
