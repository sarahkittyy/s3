#pragma once

#include <glm/glm.hpp>

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
	void set_ambient(glm::vec3 ambient);
	/// retrieve the ambient color
	glm::vec3 get_ambient() const;

	/// set the diffuse color
	void set_diffuse(glm::vec3 diffuse);
	/// retrieve the diffuse color
	glm::vec3 get_diffuse() const;

	/// set the specular color
	void set_specular(glm::vec3 specular);
	/// retrieve the specular color
	glm::vec3 get_specular() const;

	void populate(const char* context, shader& s) const;

private:
	/// light pos
	glm::vec3 m_position;

	/// light properties
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

}
