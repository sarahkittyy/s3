#pragma once

#include <s3/windowbase.hpp>

#include <s3/mouse.hpp>
#include <s3/rendertarget.hpp>
#include <s3/resource.hpp>

#include <s3/events.hpp>

#include <string>
#include <unordered_map>

namespace s3 {

class renderable;

/// primary window manager
class window : public windowbase,
			   public rendertarget,
			   public evt::emitter {
public:
	/// window constructor
	window(int width, int height, const char* title);
	~window();

	/// activate this window as the active one (for key inputs, etc)
	void activate();

	/// render the frame
	void swap();

	/// retrieve the mouse from this window instance
	mouse get_mouse();

	/// retrieve the active window
	static window& active();
	static const window& cactive();

	static s3::resource& resource();

private:
	static s3::resource m_r;   /// the app's resource manager

	evt::observer m_ob;	  /// for the window to hook into its own events

	/// for glfw callbacks to access these window mappings
	friend void glfw_key_cb(GLFWwindow*, int, int, int, int);
	friend void glfw_text_cb(GLFWwindow*, unsigned int);
	friend void glfw_mouse_move_cb(GLFWwindow*, double, double);
	friend void glfw_mouse_enter_cb(GLFWwindow*, int);
	friend void glfw_mouse_button_cb(GLFWwindow*, int, int, int);
	friend void glfw_mouse_scroll_cb(GLFWwindow*, double, double);
	friend void glfw_window_resize_cb(GLFWwindow*, int, int);

	/// mapping of glfw windows to their respective window class
	static std::unordered_map<GLFWwindow*, window*> window_map;
	static window* active_window;	/// the current active window
};

}
