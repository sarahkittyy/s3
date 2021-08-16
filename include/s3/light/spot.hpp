#pragma once

#include <s3/light/base.hpp>

namespace s3::light {

/// a spotlight
class spot : public base {
public:
	spot();

	/// set the spot light's position
	void set_pos(glm::vec3 pos);
	/// set the spot light's position
	void set_pos(float x, float y, float z);
	/// retrieve the spot light's position
	glm::vec3 get_pos() const;

	/// set the spotlight direction
	void set_dir(glm::vec3 dir);
	/// set the spotlight direction
	void set_dir(float x, float y, float z);
	/// get the spotlight direction
	glm::vec3 get_dir() const;

	/// set the spotlight angle (degrees)
	void set_angle(float angle);
	/// retrieve the spotlight angle
	float get_angle() const;

	/// set the radius of the shadow edge feathering
	void set_feather_strength(float feather);
	/// retrieve the feather strength
	float get_feather_strength() const;

	/// set the attenuation factors that determine when a light falls off
	void set_attenuation(float constant, float linear, float quadratic);

	/// populate the shader
	void populate(const char* context, shader& s) const;

private:
	/// spotlight position
	glm::vec3 m_pos;
	/// spotlight direction
	glm::vec3 m_dir;
	/// spotlight angle
	float m_angle;
	/// spotlight feathering distance
	float m_feather;

	/// attentuation factors
	float m_constant;
	float m_linear;
	float m_quadratic;
};

}
