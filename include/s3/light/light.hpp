#pragma once

#include <glm/glm.hpp>

#include <s3/color.hpp>
#include <s3/uniformstruct.hpp>

namespace s3::light {

/// a light source
class light : public uniformstruct {
public:
	/// construct the light, with an optional position
	light(glm::vec3 pos = glm::vec3(0, 10, 0));
	light(float x, float y, float z);

	/// set the light position
	void set_pos(glm::vec3 pos);
	/// retrieve the light position
	glm::vec3 get_pos() const;

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

	void populate(const char* context, shader& s) const;

private:
	/// light pos
	glm::vec3 m_position;

	/// light properties
	color m_ambient;
	color m_diffuse;
	color m_specular;
};

}
