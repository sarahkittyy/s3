#include "s3/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>

namespace s3 {

texture::texture()
	: m_tex(0),
	  m_w(0),
	  m_h(0) {
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
}

void texture::set_filter_mode(filter_mode m) {
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)m);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)m);
}

void texture::set_border_color(color bc) {
	bind();

	float c[] = { bc.r, bc.g, bc.b, bc.a };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, c);
}

void texture::set_wrap_mode(wrap_mode m) {
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)m);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)m);
}

void texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_tex);
}

void texture::del() {
	glDeleteTextures(1, &m_tex);
}

glm::vec2 texture::size() const {
	return glm::vec2(m_w, m_h);
}

}
