#pragma once

#include <s3/camera.hpp>
#include <s3/window.hpp>

#include <glm/glm.hpp>

namespace s3::cams {

/// static, fixed camera
class fixed : public camera {
public:
	/// initialized with a position and a place to look at
	fixed(glm::vec3 pos = { 0, 0, 0 }, glm::vec3 aim = { 0, 0, -1.f });
	~fixed();

	/// update the position
	void set_pos(glm::vec3 pos);
	/// retrieve the current position
	glm::vec3 get_pos() const;

	/// update the aim
	void set_aim(glm::vec3 aim);
	/// retrieve the position the camera is looking at
	glm::vec3 get_aim() const;

	glm::mat4 proj() const;
	glm::mat4 view() const;

private:
	glm::vec3 m_pos;   /// camera position
	glm::vec3 m_aim;   /// what the camera is looking at
};

}
