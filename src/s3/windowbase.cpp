#include "s3/windowbase.hpp"

#include <stdexcept>

namespace s3 {

bool windowbase::initd = false;

windowbase::windowbase(int width, int height, const char* title) {
	if (!initd) {
		glewExperimental = true;
		if (!glfwInit()) {
			throw std::runtime_error("Could not initialize glfw.");
		}
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(m_window);

	glfwSwapInterval(1);

	if (!initd) {
		if (glewInit() != GLEW_OK) {
			glfwTerminate();
			throw std::runtime_error("Could not initialize glew.");
		}
	}
	initd = true;
}

windowbase::~windowbase() {
	glfwDestroyWindow(m_window);
}

bool windowbase::should_close() const {
	return glfwWindowShouldClose(m_window);
}

glm::vec2 windowbase::pos() const {
	int x, y;
	glfwGetWindowPos(m_window, &x, &y);
	return glm::vec2(x, y);
}

void windowbase::set_mouse_capture_active(bool active) {
	if (active) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	} else {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

bool windowbase::get_mouse_capture_active() const {
	return glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

GLFWwindow* windowbase::handle() {
	return m_window;
}

}
