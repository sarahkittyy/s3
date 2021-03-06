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

	/// add a normal map
	void set_normal(texture& normal);
	/// retrieve the normal map
	texture* get_normal();

	/// add a height map
	void set_height(texture& height);
	/// retrieve the height map
	texture* get_height();
	/// set the scale of the heightmap
	void set_height_scale(float scale);
	/// retrieve the scale of the heightmap
	float get_height_scale() const;

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
	texture* m_diffuse;		/// diffuse map
	texture* m_specular;	/// specular map
	texture* m_emission;	/// emission map
	texture* m_normal;		/// normal map
	texture* m_height;		/// height map
	float m_height_scale;	/// the scale that the height map affects the object
	float m_shininess;		/// affects specular reflection
};

}
