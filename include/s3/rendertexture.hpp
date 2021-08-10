#pragma once

#include <s3/rendertarget.hpp>
#include <s3/texture.hpp>

namespace s3 {

/// framebuffer to render to a texture
class rendertexture : public rendertarget, public texture {
public:
	rendertexture(int width, int height);
	~rendertexture();

	rendertexture(const rendertexture&) = delete;
	rendertexture& operator=(const rendertexture&) = delete;

	/// free all internal opengl resources
	void del();

protected:
	/// binds the framebuffer
	void bind();

	/// make the original create fn private
	using texture::create;

private:
	/// internal framebuffer id
	GLuint m_fbo;
	/// renderbuffer for depth and stencil testing
	GLuint m_rbo;
};

}
