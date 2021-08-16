#pragma once

#include <s3/rendertarget.hpp>
#include <s3/texture.hpp>

namespace s3 {

/// framebuffer to render to a texture
class rendertexture : public rendertarget, public texture {
public:
	rendertexture(int width, int height, texture_type type = texture_type::DEFAULT);
	~rendertexture();

	rendertexture(const rendertexture&) = delete;
	rendertexture& operator=(const rendertexture&) = delete;

	/// blit this rendertexture onto the given framebuffer id
	void blit(GLuint fbo, int target_width, int target_height);
	/// blit this rendertexture onto another
	void blit(rendertarget& other);

	/// return the internal framebuffer handle
	GLuint framebuffer() const;

	/// rendertarget::size and texture::size overlap so this just makes my intellisense happy
	using rendertarget::size;

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
