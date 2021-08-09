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
	/// input size of
	rendertarget(int width, int height);
	virtual ~rendertarget();

	/// clear the target
	void flush(color col = color::from_ints(255, 255, 255));
	/// draw a renderable object
	void draw(renderable& d, drawstate ds);
	/// draw a mesh
	void draw(mesh& d, drawstate ds);

	/// retrieve the viewport size of whatever is updated
	glm::vec2 size() const;
	/// update the target viewport width
	void set_width(int width);
	/// update the target viewport height
	void set_height(int height);
	/// update the target viewport size
	void set_size(glm::vec2 size);

protected:
	/// check if this framebuffer is valid
	bool valid();

	/// reset opengl settings (culling, depth testing, etc)
	void reset_opengl();

	/// bind the framebuffer
	virtual void bind();

private:
	/// width and height of the target
	int m_width, m_height;
};

}
