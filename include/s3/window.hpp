#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <s3/color.hpp>
#include <s3/drawstate.hpp>
#include <s3/mesh.hpp>
#include <s3/mouse.hpp>
#include <s3/resource.hpp>
#include <s3/shader.hpp>

#include <s3/events.hpp>

#include <string>
#include <unordered_map>

namespace s3 {

class renderable;
class camera;

/// primary window manager
class window : public evt::emitter {
public:
	/// window constructor
	window(int width, int height, const char* title);
	~window();

	/// register a shader for use and quick switching
	void register_shader(const std::string& name, shader s);

	/// set the active shader to use
	void use_shader(const std::string& name);

	/// activates a camera for updating the proj and view matrices with
	void use_camera(camera* c);

	/// retrieve a shader given its name
	shader& shdr(const std::string& name);

	/// activate this window as the active one (for key inputs, etc)
	void activate();

	/// flush screen
	void flush(color col);
	/// draw a renderable object on screen
	void draw(renderable& d, drawstate ds = drawstate::empty);
	/// draw a mesh to the screen
	void draw(mesh& d, drawstate ds = drawstate::empty);
	/// swap buffers, finalizing this frame's render
	void swap();

	/// set the transformation model matrix
	void model(glm::mat4 matrix);

	/// returns true when the window should close.
	bool should_close() const;

	/// window size, in pixels.
	glm::vec2 size() const;
	/// absolute window position
	glm::vec2 pos() const;

	/// retrieve the mouse from this window instance
	mouse get_mouse();

	/// retrieve the active window
	static window& active();
	static const window& cactive();

	static s3::resource& resource();

	/// true to activate glfw's mouse capturing mode
	void set_mouse_capture_active(bool active = true);
	/// returns whether or not the mouse is captured or not
	bool get_mouse_capture_active() const;

	/// retrieve the internal opengl window handle
	GLFWwindow* handle();

private:
	GLFWwindow* m_window;	/// glfw window
	static bool initd;		/// has a window been constructed yet?

	static s3::resource m_r;   /// the app's resource manager

	evt::observer m_ob;	  /// for the window to hook into its own events

	camera* m_cam;	 /// camera in use

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

	std::unordered_map<std::string, shader> m_shaders;	 /// all registered shaders
	std::string m_active_shader;						 /// the currently activated shader
};

}
