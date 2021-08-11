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
	void set_diffuse(texture& tex);
	/// retrieve the diffuse map
	texture* get_diffuse();

	/// set the specular map
	void set_specular(texture& specular);
	/// retrieve the specular map
	texture* get_specular();

	/// add an emission map
	void set_emission(texture& emission);
	/// retrieve the emission map
	texture* get_emission();

	/// sets the texture for both the diffuse and specular mappings
	void set_texture(texture& tex);

	/// set how shiny the object is (higher = shinier)
	void set_shininess(float shininess);
	/// retrieve the object's shininess factor
	float get_shininess() const;

	/// reset the material to default (empty)
	void clear();

	void populate(const char* context, shader& s) const;

private:
	texture* m_diffuse;	   /// diffuse map
	texture* m_specular;   /// specular map
	texture* m_emission;   /// emission map
	float m_shininess;	   /// affects specular reflection
};

}
