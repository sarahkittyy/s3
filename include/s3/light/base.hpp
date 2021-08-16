#pragma once

#include <glm/glm.hpp>

#include <s3/color.hpp>
#include <s3/uniformstruct.hpp>

namespace s3::light {

/// an abstract light source, inherited by point, directional, and spotlight
class base : public uniformstruct {
public:
	base();
	virtual ~base();

	/// set the ambient color
	void set_ambient(color ambient);
	/// retrieve the ambient color
	color get_ambient() const;

	/// set the diffuse color
	void set_diffuse(color diffuse);
	/// retrieve the diffuse color
	color get_diffuse() const;

	/// set the specular color
	void set_specular(color specular);
	/// retrieve the specular color
	color get_specular() const;

	/// populate the shader with the light parameters
	virtual void populate(const char* context, shader& s) const;

private:
	/// light properties
	color m_ambient;
	color m_diffuse;
	color m_specular;
};

}
