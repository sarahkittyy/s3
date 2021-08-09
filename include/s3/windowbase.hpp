#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace s3 {

/// base window, for initializing glfw before the rendertarget data
class windowbase {
public:
	windowbase(int width, int height, const char* title);
	virtual ~windowbase();

	/// returns true when the window should close.
	bool should_close() const;

	/// absolute window position
	glm::vec2 pos() const;

	/// true to activate glfw's mouse capturing mode
	void set_mouse_capture_active(bool active = true);
	/// returns whether or not the mouse is captured or not
	bool get_mouse_capture_active() const;

	/// retrieve the internal opengl window handle
	GLFWwindow* handle();

protected:
	/// bare window instance
	GLFWwindow* m_window;

private:
	/// has bare glfw been set up yet?
	static bool initd;
};

}
