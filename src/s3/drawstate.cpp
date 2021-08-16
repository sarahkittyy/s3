#include "s3/drawstate.hpp"

#include <s3/window.hpp>

namespace s3 {

drawstate::drawstate()
	: transform(),
	  shader(&window::resource().shader()),
	  camera(nullptr),
	  material(nullptr) {
}

void drawstate::add_pointlight(s3::light::point& pl) {
	m_pointlights.push_back(&pl);
}

std::vector<light::point*>& drawstate::get_pointlights() {
	return m_pointlights;
}

light::point* drawstate::get_pointlight(int i) {
	return m_pointlights[i];
}

size_t drawstate::pointlight_count() const {
	return m_pointlights.size();
}

void drawstate::clear_pointlights() {
	m_pointlights.clear();
}

void drawstate::add_dirlight(s3::light::dir& dl) {
	m_dirlights.push_back(&dl);
}

std::vector<light::dir*>& drawstate::get_dirlights() {
	return m_dirlights;
}

light::dir* drawstate::get_dirlight(int i) {
	return m_dirlights[i];
}

size_t drawstate::dirlight_count() const {
	return m_dirlights.size();
}

void drawstate::clear_dirlights() {
	m_dirlights.clear();
}

void drawstate::add_spotlight(s3::light::spot& sl) {
	m_spotlights.push_back(&sl);
}

std::vector<light::spot*>& drawstate::get_spotlights() {
	return m_spotlights;
}

light::spot* drawstate::get_spotlight(int i) {
	return m_spotlights[i];
}

size_t drawstate::spotlight_count() const {
	return m_spotlights.size();
}

void drawstate::clear_spotlights() {
	m_spotlights.clear();
}

void drawstate::clear_lights() {
	clear_pointlights();
	clear_dirlights();
	clear_spotlights();
}

}
