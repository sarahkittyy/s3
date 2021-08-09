#include "s3/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>

namespace s3 {

texture::texture()
	: m_tex(0),
	  m_w(0),
	  m_h(0),
	  m_f(filter_mode::LINEAR),
	  m_bc(),
	  m_wrap(wrap_mode::CLAMP_TO_EDGE) {
}

void texture::create(int width, int height) {
	glGenTextures(1, &m_tex);
	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	update_tex_params();
}

void texture::from_file(const std::string& path) {
	glGenTextures(1, &m_tex);
	bind();

	int ch;
	unsigned char* data = stbi_load(path.c_str(), &m_w, &m_h, &ch, 0);
	if (!data) throw std::runtime_error("Could not load image " + path + ".");

	int fmt = ch == 4 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, fmt, m_w, m_h, 0, fmt, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	update_tex_params();
}

void texture::set_filter_mode(filter_mode m) {
	bind();

	m_f = m;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)m);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)m);
}

void texture::set_border_color(color bc) {
	bind();

	m_bc = bc;

	float c[] = { bc.r, bc.g, bc.b, bc.a };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, c);
}

void texture::set_wrap_mode(wrap_mode m) {
	bind();

	m_wrap = m;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)m);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)m);
}

void texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_tex);
}

GLuint texture::handle() {
	return m_tex;
}

void texture::del() {
	glDeleteTextures(1, &m_tex);
}

glm::vec2 texture::size() const {
	return glm::vec2(m_w, m_h);
}

void texture::update_tex_params() {
	set_filter_mode(m_f);
	set_border_color(m_bc);
	set_wrap_mode(m_wrap);
}

}
