#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace s3 {

/// class for abstracting matrix transformations
class transform {
public:
	transform();
	virtual ~transform();

	/// translate by the given offset
	void move(glm::vec3 by);
	/// set the absolute translation
	void set_pos(glm::vec3 pos);
	/// retrieve the current translation
	glm::vec3 get_pos() const;

	/// rotate by the given euler angles (radians)
	void rotate(glm::vec3 euler);
	/// set the rotation to the given euler angles (radians)
	void set_rotation(glm::vec3 euler);
	/// get the rotation, in euler angles (radians)
	glm::vec3 get_euler_rotation() const;

	/// scale by the given factors
	void scale(glm::vec3 by);
	/// set the absolute scale to the given factors
	void set_scale(glm::vec3 scale);
	/// retrieve the scaling of this transform
	glm::vec3 get_scale() const;
	
	/// combine two transformations
	transform operator*(const transform& other) const;
	/// combine a translation with this one
	transform& operator*=(const transform& other);

	/// return the entire combined transformation as a matrix.
	glm::mat4 matrix() const;

private:
	glm::vec3 m_trans;	 /// internal translation
	glm::quat m_rot;	 /// internal rotation
	glm::vec3 m_scale;	 /// internal scaling
};

}
