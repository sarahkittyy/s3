#pragma once

#include <GL/glew.h>

namespace s3 {

class uniformstruct;

/**
 * @brief class for managing, compiling, and loading shaders.
 */
class shader {
public:
	/**
	 * @brief constructor
	 *
	 * @param vs the source of the vertex shader
	 * @param fs the source of the fragment shader
	 */
	shader(const char* vs, const char* fs);

	/**
	 * @brief initialize with the default shader settings
	 */
	shader();

	/**
	 * @brief deconstructs all internal opengl data
	 *
	 */
	~shader();

	shader(const shader&) = delete;
	shader& operator=(const shader&) = delete;

	/**
	 * @brief move constructor
	 *
	 */
	shader(shader&& other) noexcept;

	/**
	 * @brief set this shader as active and use it for rendering
	 */
	void use();

	/**
	 * @brief internal opengl shader program id
	 */
	unsigned int id() const;

	/**
	 * @brief set a uniform inside this shader
	 *
	 * @param name the name of the uniform
	 * @param data the value to copy over
	 */
	template <typename T>
	void set_uniform(const char* name, const T& data);

private:
	const char *m_vs, *m_fs;   /// shader sources
	GLuint m_prog;			   /// stored program
	void compile();			   /// compile the shader
};

}
