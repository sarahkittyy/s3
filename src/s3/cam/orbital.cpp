#include "s3/cam/orbital.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

namespace s3::cams {

orbital::orbital()
	: m_ob(window()),
	  m_center(0, 0, 0),
	  m_pos(0, 0, -1),
	  m_dist(3.0f),
	  m_mouse_x(0),
	  m_mouse_y(0),
	  m_mouse_px(0),
	  m_mouse_py(0),
	  m_sens(0.1f),
	  m_azimuth(0.0f),
	  m_polar(0.0f),
	  m_on_click(false),
	  m_btn(mouse::LEFT),
	  m_first_mouse(true) {

	m_ob.hook(evt::MOUSE_MOVE, [this](const evt::data& d) {
		m_mouse_x = (float)d.get<double>("x");
		m_mouse_y = (float)d.get<double>("y");

		if (m_first_mouse) {
			m_first_mouse = false;
			m_mouse_px	  = m_mouse_x;
			m_mouse_py	  = m_mouse_y;
		}
	});

	m_ob.hook(evt::MOUSE_SCROLL, [this](const evt::data& d) {
		float y = (float)d.get<double>("y");

		set_dist(get_dist() + y);
	});
}

orbital::~orbital() {
}

void orbital::update() {
	// get mouse pos diffs
	float mdx, mdy;
	mdx = m_mouse_px - m_mouse_x;
	mdy = m_mouse_py - m_mouse_y;

	mdx *= m_sens;
	mdy *= m_sens;

	if (mdx != 0 || mdy != 0) {
		m_mouse_px = m_mouse_x;
		m_mouse_py = m_mouse_y;
	}

	if (window().get_mouse().btn(m_btn) == mouse::PRESSED || !m_on_click) {
		m_azimuth -= mdx;
		m_azimuth = fmod(m_azimuth, 0, 360);

		m_polar -= mdy;
		m_polar = std::clamp(m_polar, -89.9f, 89.9f);
	}

	update_pos();
}

glm::mat4 orbital::proj() const {
	return glm::perspective(glm::radians(45.f), window().size().x / window().size().y, 0.1f, 100.f);
}

glm::mat4 orbital::view() const {
	return glm::lookAt(m_pos, m_center, glm::vec3(0, 1, 0));
}

void orbital::update_pos() {
	m_pos.x =
		m_center.x +
		m_dist *
			std::cos(glm::radians(m_polar)) *
			std::cos(glm::radians(m_azimuth));
	m_pos.y =
		m_center.y +
		m_dist *
			std::sin(glm::radians(m_polar));
	m_pos.z =
		m_center.z +
		m_dist *
			std::cos(glm::radians(m_polar)) *
			std::sin(glm::radians(m_azimuth));
}

void orbital::set_pos(glm::vec3 pos) {
	m_pos = pos;
}

glm::vec3 orbital::get_pos() const {
	return m_pos;
}

void orbital::set_dist(float dist) {
	m_dist = dist;
	if (m_dist < 0) {
		m_dist = 0.1f;
	}
}

float orbital::get_dist() const {
	return m_dist;
}

void orbital::set_sens(float sens) {
	m_sens = sens;
}

float orbital::get_sens() const {
	return m_sens;
}

void orbital::set_onclick(bool set) {
	m_on_click = set;
}

bool orbital::get_onclick() const {
	return m_on_click;
}

void orbital::set_onclick_btn(mouse::button btn) {
	m_btn = btn;
}

mouse::button orbital::get_onclick_btn() const {
	return m_btn;
}

float orbital::fmod(float v, float lo, float hi) {
	float t = std::fmod(v - lo, hi - lo);
	return t < 0 ? t + hi : t + lo;
}

}
