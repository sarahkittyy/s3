#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include <s3/material.hpp>
#include <s3/mesh.hpp>
#include <s3/renderable.hpp>
#include <s3/texture.hpp>

namespace s3::obj {

/// a static skybox
class skybox : public renderable {
public:
	/// construct the skybox given a list of paths (order: r, l, t, bot, f, back)
	skybox(std::vector<std::string> paths);
	~skybox();

	/// non-copyable to prevent deleting internal vertex data
	skybox(const skybox&) = delete;
	skybox& operator=(const skybox&) = delete;

private:
	void draw(rendertarget& target, drawstate ds);

	texture m_tex;	   /// cubemap texture
	shader m_shader;   /// custom skybox shader

	/// array and buffer to store cube vertex data
	GLuint m_vao, m_vbo;

	void bind();   /// bind the vao

	void gl_draw();	  /// raw opengl rendering
};

}
