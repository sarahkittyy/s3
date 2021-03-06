#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace s3 {

class window;

/// class retrieved from window.mouse(), providing an api for retrieving mouse info
class mouse {
public:
	enum state {
		PRESSED	 = GLFW_PRESS,
		RELEASED = GLFW_RELEASE,
	};

	enum button {
		LEFT   = GLFW_MOUSE_BUTTON_LEFT,
		RIGHT  = GLFW_MOUSE_BUTTON_RIGHT,
		MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
	};

	/// get the current mouse position
	glm::vec2 get_pos();

	/// get the state of the left mouse button
	state left_btn();
	/// get the state of the right mouse button
	state right_btn();
	/// get the state of the middle mouse button
	state middle_btn();

	/// get the state of the given button
	state btn(button b);

private:
	friend class window;

	mouse(window& w);
	window& m_window;
};

}
