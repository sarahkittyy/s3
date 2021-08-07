#include "s3/mouse.hpp"

#include <s3/window.hpp>

namespace s3 {

mouse::mouse(window& w)
	: m_window(w) {
}

glm::vec2 mouse::get_pos() {
	double xp, yp;
	glfwGetCursorPos(m_window.handle(), &xp, &yp);
	return glm::vec2(xp, yp);
}

mouse::state mouse::left_btn() {
	return (state)glfwGetMouseButton(m_window.handle(), GLFW_MOUSE_BUTTON_LEFT);
}

mouse::state mouse::right_btn() {
	return (state)glfwGetMouseButton(m_window.handle(), GLFW_MOUSE_BUTTON_RIGHT);
}

mouse::state mouse::middle_btn() {
	return (state)glfwGetMouseButton(m_window.handle(), GLFW_MOUSE_BUTTON_MIDDLE);
}

mouse::state mouse::btn(button b) {
	return (state)glfwGetMouseButton(m_window.handle(), (int)b);
}

}
