#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <type_traits>
#include <vector>

#include <s3/color.hpp>

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

enum class texture_type {
	DEFAULT		= GL_TEXTURE_2D,
	CUBEMAP		= GL_TEXTURE_CUBE_MAP,
	MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
};

/**
 * @brief usable opengl texture
 */
class texture {
public:
	texture(texture_type type = texture_type::DEFAULT);
	~texture();

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
	 * @brief load the texture given a file path
	 *
	 * @param path the path to the file
	 */
	void from_file(const std::string& path);

	/**
	 * @brief load the texture given paths to cubemap faces
	 *
	 * @param paths the paths to the cubemap, in order r, l, t, bot, f, back
	 */
	void from_cubemap(std::vector<std::string> paths);

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
	 * 
	 * @param unit the texture unit to bind this to
	 */
	void bind(int unit = 0) const;

	/**
	 * @brief bind an empty texture to the given unit
	 *
	 * @param unit the texture unit to clear
	 */
	static void unbind(int unit = 0, texture_type type = texture_type::DEFAULT);

	/**
	 * @brief retrieve the internal opengl texture id
	 *
	 * @return GLuint the texture ID
	 */
	GLuint handle() const;

	/**
	 * @brief retrieve the internal texture's type
	 *
	 * @return texture_type
	 */
	texture_type get_type() const;

private:
	const texture_type m_type;	 /// the internal texture type
	GLuint m_tex;				 /// opengl texture
	int m_w, m_h;				 /// texture dimensions

	filter_mode m_f;	/// filter mode
	color m_bc;			/// border color
	wrap_mode m_wrap;	/// wrap mode



	/**
	 * @brief update the texture params based on the saved values
	 *
	 */
	void update_tex_params() {
		set_filter_mode(m_f);
		set_border_color(m_bc);
		set_wrap_mode(m_wrap);
	}
};

}
