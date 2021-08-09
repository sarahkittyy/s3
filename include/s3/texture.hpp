#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <s3/color.hpp>
#include <string>

namespace s3 {

enum class wrap_mode {
	REPEAT			= GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
};

enum class filter_mode {
	NEAREST = GL_NEAREST,
	LINEAR	= GL_LINEAR,
};

/**
 * @brief usable opengl texture
 */
class texture {
public:
	texture();

	texture(const texture&) = delete;
	texture& operator=(const texture&) = delete;

	/**
	 * @brief creates an empty texture with the given width and height
	 *
	 * @param width
	 * @param height
	 */
	virtual void create(int width, int height);

	/**
	 * @brief load a texture given a file path
	 *
	 * @param path the path to the file
	 */
	void from_file(const std::string& path);

	/**
	 * @brief delete internal opengl data
	 */
	void del();

	/**
	 * @brief set opengl's texture filtering mode
	 *
	 * @param m
	 */
	void set_filter_mode(filter_mode m);

	/**
	 * @brief set opengl's texture wrapping mode
	 *
	 * @param m
	 */
	void set_wrap_mode(wrap_mode m);

	/**
	 * @brief in the case of GL_CLAMP_TO_BORDER, set the border color.
	 *
	 * @param bc
	 */
	void set_border_color(color bc);

	/**
	 * @brief get the size of the image.
	 */
	glm::vec2 size() const;

	/**
	 * @brief bind the texture for use
	 */
	void bind();

	/**
	 * @brief retrieve the internal opengl texture id
	 *
	 * @return GLuint the texture ID
	 */
	GLuint handle();

private:
	GLuint m_tex;	/// opengl texture
	int m_w, m_h;	/// texture dimensions

	filter_mode m_f;	/// filter mode
	color m_bc;			/// border color
	wrap_mode m_wrap;	/// wrap mode

	/**
	 * @brief update the texture params based on the saved values
	 *
	 */
	void update_tex_params();
};

}
