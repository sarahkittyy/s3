#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <s3/color.hpp>
#include <s3/drawstate.hpp>
#include <s3/mesh.hpp>
#include <s3/renderable.hpp>
#include <s3/texture.hpp>

namespace s3 {

/// abstract rendertarget object. inherited by window and rendertexture.
class rendertarget {
public:
	rendertarget();
	virtual ~rendertarget();

	/// clear the target
	void flush(color col = color::from_ints(255, 255, 255));
	/// draw a renderable object
	void draw(renderable& d, drawstate ds);
	/// draw a mesh
	void draw(mesh& d, drawstate ds);

protected:
	/// check if this framebuffer is valid
	bool valid();

	/// bind the framebuffer
	void bind();

private:
	/// framebuffer id
	GLuint m_fbo;
};

}
