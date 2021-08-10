#pragma once

#include <glm/glm.hpp>

#include <s3/texture.hpp>
#include <s3/uniformstruct.hpp>

namespace s3 {

/// a material that defines how light affects a respective surface
class material : public uniformstruct {
public:
	/// default material properties
	material();
	virtual ~material();

	/// set the diffuse map
	void set_diffuse(const texture& tex);
	/// retrieve the diffuse map
	const texture& get_diffuse() const;

	/// set the specular color
	void set_specular(const texture& specular);
	/// retrieve the specular color
	const texture& get_specular() const;

	/// sets the texture for both the diffuse and specular mappings
	void set_texture(const texture& tex);

	/// set how shiny the object is (higher = shinier)
	void set_shininess(float shininess);
	/// retrieve the object's shininess factor
	float get_shininess() const;

	void populate(const char* context, shader& s) const;

private:
	const texture* m_diffuse;
	const texture* m_specular;
	float m_shininess;
};

}
