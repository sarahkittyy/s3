#include "s3/window.hpp"

#include <glm/gtc/matrix_access.hpp>
#include <stdexcept>

#include <s3/camera.hpp>
#include <s3/mouse.hpp>
#include <s3/renderable.hpp>

namespace s3 {

bool window::initd = false;
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
	: m_ob(*this),
	  m_cam(nullptr),
	  m_active_shader("") {
	if (!initd) {
		glewExperimental = true;
		if (!glfwInit()) {
			throw std::runtime_error("Could not initialize glfw.");
		}
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwMakeContextCurrent(m_window);

	if (!initd) {
		if (glewInit() != GLEW_OK) {
			glfwTerminate();
			throw std::runtime_error("Could not initialize glew.");
		}
	}
	initd = true;

	window_map[m_window] = this;
	activate();

	glfwSetKeyCallback(m_window, glfw_key_cb);
	glfwSetCharCallback(m_window, glfw_text_cb);
	glfwSetCursorPosCallback(m_window, glfw_mouse_move_cb);
	glfwSetCursorEnterCallback(m_window, glfw_mouse_enter_cb);
	glfwSetMouseButtonCallback(m_window, glfw_mouse_button_cb);
	glfwSetScrollCallback(m_window, glfw_mouse_scroll_cb);
	glfwSetWindowSizeCallback(m_window, glfw_window_resize_cb);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glFrontFace(GL_CCW);

	register_shader("default", shader());
	shdr("default").set_uniform("model", glm::mat4(1.0f));

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
	glfwDestroyWindow(m_window);
}

void window::register_shader(const std::string& name, shader s) {
	m_shaders[name] = s;
	if (m_active_shader.empty()) {
		use_shader(name);
	}
}

void window::use_shader(const std::string& name) {
	if (!m_shaders.contains(name))
		throw std::runtime_error("Could not find shader with name " + name + ".");
	if (m_active_shader == name) return;
	m_shaders[name].use();
	m_active_shader = name;
}

void window::use_camera(camera* c) {
	m_cam = c;
}

shader& window::shdr(const std::string& name) {
	if (!m_shaders.contains(name))
		throw std::runtime_error("Could not find shader with name " + name + ".");
	return m_shaders[name];
}

void window::activate() {
	active_window = this;
}

void window::flush(color col) {
	glfwPollEvents();

	if (m_cam != nullptr) {
		m_cam->update();
		shdr(m_active_shader).set_uniform("proj", m_cam->proj());
		shdr(m_active_shader).set_uniform("view", m_cam->view());
	}

	glClearColor(col.r, col.g, col.b, col.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window::draw(renderable& d, drawstate ds) {
	d.draw(*this, ds);
}

void window::draw(mesh& m, drawstate ds) {
	if (ds.shader) {
		ds.shader->use();
	}
	if (ds.texture) {
		ds.texture->bind();
	}
	model(ds.transform.matrix());
	m.draw();
}

void window::swap() {
	glfwSwapBuffers(m_window);
}

void window::model(glm::mat4 matrix) {
	shdr(m_active_shader).set_uniform("model", glm::mat4(matrix));
}

bool window::should_close() const {
	return glfwWindowShouldClose(m_window);
}

glm::vec2 window::size() const {
	int x, y;
	glfwGetWindowSize(m_window, &x, &y);
	return glm::vec2(x, y);
}

glm::vec2 window::pos() const {
	int x, y;
	glfwGetWindowPos(m_window, &x, &y);
	return glm::vec2(x, y);
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

void window::set_mouse_capture_active(bool active) {
	if (active) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	} else {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

bool window::get_mouse_capture_active() const {
	return glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

GLFWwindow* window::handle() {
	return m_window;
}

}
