#pragma once

#include <glm/glm.hpp>

#include <s3/light/base.hpp>

namespace s3::light {

/// a point light that radiates in all directions
class point : public base {
public:
	point();
	/// initialize the pointlight with a position
	point(glm::vec3 pos);
	/// initialize the pointlight with a position
	point(float x, float y, float z);

	/// set the point light's position
	void set_pos(glm::vec3 pos);
	/// set the point light's position
	void set_pos(float x, float y, float z);
	/// retrieve the point light's position
	glm::vec3 get_pos() const;

	/// set the attenuation factors that determine when a light falls off
	void set_attenuation(float constant, float linear, float quadratic);

	/// populate the shader
	void populate(const char* context, shader& s) const;

private:
	/// point light's position
	glm::vec3 m_pos;

	/// attentuation factors
	float m_constant;
	float m_linear;
	float m_quadratic;
};

}
