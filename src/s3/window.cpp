#include "s3/window.hpp"

#include <glm/gtc/matrix_access.hpp>
#include <stdexcept>

#include <s3/camera.hpp>
#include <s3/mouse.hpp>
#include <s3/renderable.hpp>

namespace s3 {

std::unordered_map<GLFWwindow*, window*> window::window_map;
window* window::active_window;
s3::resource window::m_r;

///////////////////////////// glfw event handlers ////////////////////////////////

/// for key presses, releases, etc - game input style
void glfw_key_cb(GLFWwindow* gl_win, int key, int scancode, int action, int mods) {
	window& win = *window::window_map[gl_win];
	win.emit(evt::KEY_INPUT,
			 evt::data()
				 .set("action", action)
				 .set("key", key)
				 .set("mods", mods));
}

/// for text input - typing text style
void glfw_text_cb(GLFWwindow* gl_win, unsigned int codepoint) {
	window& win = *window::window_map[gl_win];
	win.emit(evt::TEXT_INPUT,
			 evt::data()
				 .set("code", codepoint));
}

/// for when the mouse moves
void glfw_mouse_move_cb(GLFWwindow* gl_win, double x, double y) {
	window& win = *window::window_map[gl_win];
	win.emit(evt::MOUSE_MOVE,
			 evt::data()
				 .set("x", x)
				 .set("y", y));
}

/// for when the mouse enters / leaves the window
void glfw_mouse_enter_cb(GLFWwindow* gl_win, int entered) {
	window& win = *window::window_map[gl_win];
	if (entered) {
		win.emit(evt::MOUSE_ENTER, evt::data());
	} else {
		win.emit(evt::MOUSE_EXIT, evt::data());
	}
}

/// for when a mouse button is pressed
void glfw_mouse_button_cb(GLFWwindow* gl_win, int button, int action, int mods) {
	window& win = *window::window_map[gl_win];
	win.emit(evt::MOUSE_BUTTON,
			 evt::data()
				 .set("action", action)
				 .set("button", button));
}

/// for when the mouse wheel is scrolled
void glfw_mouse_scroll_cb(GLFWwindow* gl_win, double xoffset, double yoffset) {
	window& win = *window::window_map[gl_win];
	win.emit(evt::MOUSE_SCROLL,
			 evt::data()
				 .set("x", xoffset)
				 .set("y", yoffset));
}

/// for when the window is resized
void glfw_window_resize_cb(GLFWwindow* gl_win, int w, int h) {
	window& win = *window::window_map[gl_win];
	win.emit(evt::WINDOW_RESIZE,
			 evt::data()
				 .set("width", w)
				 .set("height", h));
}

///////////////////////////// normal methods /////////////////////////////////////

window::window(int width, int height, const char* title)
	: windowbase(width, height, title),
	  m_ob(*this) {

	window_map[m_window] = this;
	activate();

	glfwSetKeyCallback(m_window, glfw_key_cb);
	glfwSetCharCallback(m_window, glfw_text_cb);
	glfwSetCursorPosCallback(m_window, glfw_mouse_move_cb);
	glfwSetCursorEnterCallback(m_window, glfw_mouse_enter_cb);
	glfwSetMouseButtonCallback(m_window, glfw_mouse_button_cb);
	glfwSetScrollCallback(m_window, glfw_mouse_scroll_cb);
	glfwSetWindowSizeCallback(m_window, glfw_window_resize_cb);

	// TODO: abstract
	m_ob.hook(evt::KEY_INPUT, [this](const evt::data& d) {
		int key = d.get<int>("key");
		int act = d.get<int>("action");
		if (act == GLFW_RELEASE && key == GLFW_KEY_ESCAPE) {
			set_mouse_capture_active(!get_mouse_capture_active());
		}
	});
}

window::~window() {
}

void window::activate() {
	active_window = this;
}

void window::clear(color col) {
	flush(col);
}

void window::swap() {
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

mouse window::get_mouse() {
	return mouse(*this);
}

window& window::active() {
	return *active_window;
}

const window& window::cactive() {
	return *active_window;
}

s3::resource& window::resource() {
	return m_r;
}

}
