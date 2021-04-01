#pragma once

#include <GL/glew.h>
#include <s3/evt/data.hpp>
#include <s3/evt/emitter.hpp>
#include <s3/evt/observer.hpp>

namespace s3::evt {

enum event {
	/**
	 * action - int - GLFW_PRESS, GLFW_REPEAT, GLFW_RELEASE
	 * key - int - GLFW_KEY_xxx
	 * mods - int - glfw modifier bits (caps, shift, etc)
	 */
	KEY_INPUT,
	/**
	 * code - uint - unicode character codepoint
	 */
	TEXT_INPUT,
	/**
	 * x - double - x position
	 * y - double - y position
	 */
	MOUSE_MOVE,
	/**
	 * no additional data
	 */
	MOUSE_ENTER,
	/**
	 * no additional data
	 */
	MOUSE_EXIT,
	/**
	 * action - int - GLFW_PRESS, GLFW_RELEASE
	 * button - int - GLFW_MOUSE_BUTTON_xxx
	 */
	MOUSE_BUTTON,
	/**
	 * x - double - x offset
	 * y - double - y offset
	 */
	MOUSE_SCROLL,
	/**
	 * width - int
	 * height - int
	 */
	WINDOW_RESIZE,
};

}
