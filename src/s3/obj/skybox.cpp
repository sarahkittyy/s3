#include "s3/obj/skybox.hpp"

namespace s3::obj {

static float skybox_vertices[] = {
	// positions
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

static const char* skybox_vs = R"shader(
#version 330 core

layout (location = 0) in vec3 pos;

out vec3 uvV;

uniform mat4 proj;
uniform mat4 view;

void main() {
	uvV = pos;
	gl_Position = (proj * view * vec4(pos, 1.0)).xyww;
}

)shader";

static const char* skybox_fs = R"shader(
#version 330 core

out vec4 color;

in vec3 uvV;

uniform samplerCube skybox;

void main() {
	color = texture(skybox, uvV);
}

)shader";

skybox::skybox(std::vector<std::string> paths)
	: m_tex(texture_type::CUBEMAP),
	  m_shader(skybox_vs, skybox_fs),
	  m_vao(0),
	  m_vbo(0) {
	m_tex.from_cubemap(paths);

	glGenVertexArrays(1, &m_vao);
	bind();

	glGenBuffers(1, &m_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER,
				 sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
}

skybox::~skybox() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void skybox::draw(rendertarget& target, drawstate ds) {
	glDepthFunc(GL_LEQUAL);
	if (!ds.camera) {
		throw std::runtime_error("Cannot render without a camera!");
	} else {
		ds.camera->update();
	}
	bind();
	m_shader.use();
	m_shader.set_uniform("proj", ds.camera->proj(target));
	m_shader.set_uniform("view", glm::mat4(glm::mat3(ds.camera->view(target))));
	m_shader.set_uniform("skybox", (int)0);
	m_tex.bind();
	gl_draw();
	glDepthFunc(GL_LESS);
}

void skybox::bind() {
	glBindVertexArray(m_vao);
}

void skybox::gl_draw() {
	glDrawArrays(GL_TRIANGLES, 0, sizeof(skybox_vertices) / (sizeof(float) * 3));
}

}
