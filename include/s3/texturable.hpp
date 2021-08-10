#pragma once

#include <s3/texture.hpp>

namespace s3 {

/// inheritable by renderables to give them a texture and an interface for accessing it
class texturable {
public:
	texturable();
	virtual ~texturable();

	/// set the texture to use
	void set_texture(const s3::texture& tex);
	/// retrieve the currently used texture
	const s3::texture* texture() const;
	/// returns true if the internal texture is not NULL
	bool has_texture() const;

private:
	const s3::texture* m_tex;
};

}
