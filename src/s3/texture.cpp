#include "s3/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>

namespace s3 {

texture::texture(texture_type type)
	: m_type(type),
	  m_tex(0),
	  m_w(0),
	  m_h(0),
	  m_f(filter_mode::LINEAR),
	  m_bc(),
	  m_wrap(wrap_mode::CLAMP_TO_EDGE) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

texture::~texture() {
	glDeleteTextures(1, &m_tex);
}

void texture::create(int width, int height) {
	glGenTextures(1, &m_tex);
	bind();

	m_w = width;
	m_h = height;

	if (get_type() == texture_type::DEFAULT) {
		glTexImage2D(GL_TEXTURE_2D,
					 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	} else if (get_type() == texture_type::CUBEMAP) {
		for (int i = 0; i < 6; ++i) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		}
	} else if (get_type() == texture_type::MULTISAMPLE) {
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,
								4,	 // 4 samples for now, TODO: make configurable
								GL_RGBA, width, height, GL_TRUE);
	}

	update_tex_params();
}

void texture::from_file(const std::string& path) {
	if (get_type() != texture_type::DEFAULT) {
		throw std::runtime_error("Cannot load an image onto a non-default texture type!");
	}
	glGenTextures(1, &m_tex);
	bind();

	int ch;
	unsigned char* data = stbi_load(path.c_str(), &m_w, &m_h, &ch, 0);
	if (!data) throw std::runtime_error("Could not load image " + path + ".");

	int fmt = ch == 4 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, fmt, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	update_tex_params();
}

void texture::from_cubemap(std::vector<std::string> paths) {
	if (get_type() != texture_type::CUBEMAP) {
		throw std::runtime_error("Cannot load a cubemap onto a non-cubemap texture!");
	}
	glGenTextures(1, &m_tex);
	bind();

	int ch;
	for (int i = 0; i < paths.size(); ++i) {
		stbi_set_flip_vertically_on_load(false);
		unsigned char* data = stbi_load(paths[i].c_str(), &m_w, &m_h, &ch, 0);
		if (!data) throw std::runtime_error("Could not load image " + paths[i] + ".");

		int fmt = ch == 4 ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					 0, GL_RGBA, m_w, m_h, 0, fmt, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	update_tex_params();
}

void texture::set_filter_mode(filter_mode m) {
	bind();

	m_f = m;

	glTexParameteri((GLenum)get_type(), GL_TEXTURE_MAG_FILTER, (GLenum)m);
	glTexParameteri((GLenum)get_type(), GL_TEXTURE_MIN_FILTER, (GLenum)m);
}

void texture::set_wrap_mode(wrap_mode m) {
	bind();

	m_wrap = m;

	glTexParameteri((GLenum)get_type(), GL_TEXTURE_WRAP_S, (GLenum)m);
	glTexParameteri((GLenum)get_type(), GL_TEXTURE_WRAP_T, (GLenum)m);
	if (get_type() == texture_type::CUBEMAP) {
		glTexParameteri((GLenum)get_type(), GL_TEXTURE_WRAP_R, (GLenum)m);
	}
}

void texture::set_border_color(color bc) {
	bind();

	m_bc = bc;

	float c[] = { bc.r, bc.g, bc.b, bc.a };
	glTexParameterfv((GLenum)get_type(), GL_TEXTURE_BORDER_COLOR, c);
}

glm::vec2 texture::size() const {
	return glm::vec2(m_w, m_h);
}

void texture::bind(int unit) const {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture((GLenum)get_type(), m_tex);
}

void texture::unbind(int unit, texture_type type) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture((GLenum)type, 0);
}

GLuint texture::handle() const {
	return m_tex;
}

texture_type texture::get_type() const {
	return m_type;
}

}
