#include "s3/cam/free.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <cmath>

namespace s3::cams {

free::free()
	: m_pos(0, 0, 0),
	  m_vel(0, 0, 0),
	  m_facing(0, 0, -1.f),
	  m_ob(window()),
	  m_mouse_x(0),
	  m_mouse_y(0),
	  m_mouse_px(0),
	  m_mouse_py(0),
	  m_mouse_pitch(0),
	  m_mouse_yaw(0),
	  m_first_mouse(true),
	  m_accel(0.35f),
	  m_sens(0.1f),
	  m_mvel(3.0f) {

	m_ob.hook(evt::MOUSE_MOVE, [this](const evt::data& d) {
		m_mouse_x = (float)d.get<double>("x");
		m_mouse_y = (float)d.get<double>("y");

		if (m_first_mouse) {
			m_first_mouse = false;
			m_mouse_px	  = m_mouse_x;
			m_mouse_py	  = m_mouse_y;
		}
	});
}

free::~free() {
}

void free::update() {
	float dt = m_clock.restart().as_seconds();

	// getting mouse position diffs
	float mdx, mdy;
	mdx = m_mouse_px - m_mouse_x;
	mdy = m_mouse_py - m_mouse_y;

	mdx *= m_sens;
	mdy *= m_sens;

	if (mdx != 0 || mdy != 0) {
		// updating "prior" mouse position
		m_mouse_px = m_mouse_x;
		m_mouse_py = m_mouse_y;

		m_mouse_yaw -= mdx;
		m_mouse_pitch += mdy;

		if (m_mouse_pitch > 89.f) m_mouse_pitch = 89.f;
		if (m_mouse_pitch < -89.f) m_mouse_pitch = -89.f;

		// https://learnopengl.com/Getting-started/Camera
		glm::vec3 dir;
		dir.x	 = cos(glm::radians(m_mouse_yaw)) * cos(glm::radians(m_mouse_pitch));
		dir.y	 = sin(glm::radians(m_mouse_pitch));
		dir.z	 = sin(glm::radians(m_mouse_yaw)) * cos(glm::radians(m_mouse_pitch));
		m_facing = glm::normalize(dir);
	}

	/// key inputs
	if (glfwGetKey(window().handle(), FORWARD_KEY) == GLFW_PRESS) {
		m_vel += glm::normalize(glm::vec3(m_facing.x, 0, m_facing.z)) * m_accel;
	} else if (glfwGetKey(window().handle(), BACKWARD_KEY) == GLFW_PRESS) {
		m_vel -= glm::normalize(glm::vec3(m_facing.x, 0, m_facing.z)) * m_accel;
	} else {
		m_vel = decel(m_vel, glm::vec3(m_facing.x, 0, m_facing.z));
	}

	if (glfwGetKey(window().handle(), LEFT_KEY) == GLFW_PRESS) {
		m_vel -= glm::normalize(glm::cross(m_facing, UP)) * m_accel;
	} else if (glfwGetKey(window().handle(), RIGHT_KEY) == GLFW_PRESS) {
		m_vel += glm::normalize(glm::cross(m_facing, UP)) * m_accel;
	} else {
		m_vel = decel(m_vel, glm::cross(m_facing, UP));
	}

	if (glfwGetKey(window().handle(), UP_KEY) == GLFW_PRESS) {
		m_vel.y += m_accel;
	} else if (glfwGetKey(window().handle(), DOWN_KEY) == GLFW_PRESS) {
		m_vel.y -= m_accel;
	} else {
		m_vel = decel(m_vel, glm::vec3(0, 1, 0));
	}

	if (glm::length(m_vel) > m_mvel) {
		m_vel = glm::normalize(m_vel) * m_mvel;
	}

	m_pos += m_vel * dt;
}

glm::mat4 free::proj(const rendertarget& target) const {
	return glm::perspective(glm::radians(45.0f), target.size().x / target.size().y, 0.1f, 100.f);
}

glm::mat4 free::view(const rendertarget& target) const {
	return glm::lookAt(m_pos, m_pos + m_facing, UP);
}

glm::vec3 free::position() const {
	return m_pos;
}

void free::set_sens(float sens) {
	m_sens = sens;
}

float free::get_sens() const {
	return m_sens;
}

void free::set_accel(float accel) {
	m_accel = accel;
}

float free::get_accel() const {
	return m_accel;
}

void free::set_maxvel(float mvel) {
	m_mvel = mvel;
}

float free::get_maxvel() const {
	return m_mvel;
}

void free::set_dir(float pitch, float yaw) {
	m_mouse_pitch = pitch;
	m_mouse_yaw	  = yaw;
	if (m_mouse_pitch > 89.f) m_mouse_pitch = 89.f;
	if (m_mouse_pitch < -89.f) m_mouse_pitch = -89.f;
	glm::vec3 dir;
	dir.x	 = cos(glm::radians(m_mouse_yaw)) * cos(glm::radians(m_mouse_pitch));
	dir.y	 = sin(glm::radians(m_mouse_pitch));
	dir.z	 = sin(glm::radians(m_mouse_yaw)) * cos(glm::radians(m_mouse_pitch));
	m_facing = glm::normalize(dir);
}

void free::set_pos(glm::vec3 pos) {
	m_pos		  = pos;
	glm::vec3 d	  = m_facing - pos;
	m_mouse_pitch = glm::degrees(std::asin(d.y / glm::length(d)));
	m_mouse_yaw	  = glm::degrees(std::atan2(d.z, d.x));
	set_dir(m_mouse_pitch, m_mouse_yaw);
}

glm::vec3 free::get_pos() const {
	return m_pos;
}

float free::decel(float v) {
	if (v > m_accel) {
		v -= (m_accel * 1.9f);
	} else if (v < -m_accel) {
		v += (m_accel * 1.9f);
	} else {
		v = 0;
	}
	return v;
}

float free::proj(glm::vec3 vec, glm::vec3 on) {
	return glm::dot(glm::normalize(on), vec);
}

glm::vec3 free::decel(glm::vec3 vec, glm::vec3 dir) {
	glm::vec3 dirc	= glm::normalize(dir) * proj(vec, dir);
	glm::vec3 compc = vec - dirc;
	float mag		= glm::length(dirc);
	if (mag > m_accel) {
		mag -= (m_accel * 1.9f);
		dirc = glm::normalize(dirc) * mag;
	} else if (glm::length(dirc) < -m_accel) {
		mag += (m_accel * 1.9f);
		dirc = glm::normalize(dirc) * mag;
	} else {
		dirc = glm::vec3(0, 0, 0);
	}
	return dirc + compc;
}

}
