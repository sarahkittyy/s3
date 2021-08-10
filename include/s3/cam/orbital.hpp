#pragma once

#include <s3/camera.hpp>
#include <s3/window.hpp>

#include <glm/glm.hpp>

namespace s3::cams {

/// orbital style camera for orbiting around a fixed point
class orbital : public camera {
public:
	orbital();
	~orbital();

	glm::mat4 proj(const rendertarget& target) const;
	glm::mat4 view(const rendertarget& target) const;
	glm::vec3 position() const;

	void update();

	/// set the central focus point of the camera
	void set_pos(glm::vec3 pos);
	/// retrieve the center point of the camera
	glm::vec3 get_pos() const;

	/// set the constant distance from the camera to the point
	void set_dist(float dist);
	/// retrieve the distance from the camera to the point
	float get_dist() const;

	/// sets the mouse sensitivity (defualt 0.1)
	void set_sens(float sens);
	/// retrieve the current mouse sensitivity
	float get_sens() const;

	/// if true, will only orbit when a mouse button is held.
	void set_onclick(bool set);
	/// retrieve whether or not onclick is set
	bool get_onclick() const;

	/// set the button to be held for onclick movement
	void set_onclick_btn(mouse::button btn);
	/// get the button to be held for onclick movement
	mouse::button get_onclick_btn() const;

private:
	/// for observing mouse events
	evt::observer m_ob;

	/// central point
	glm::vec3 m_center;
	/// camera point
	glm::vec3 m_pos;
	/// uses the current angles to update the camera's position
	void update_pos();
	/// distance from point
	float m_dist;

	/// current mouse position
	float m_mouse_x, m_mouse_y;
	/// previous mouse position
	float m_mouse_px, m_mouse_py;
	/// mouse sensitivity
	float m_sens;

	/// angle around y axis (degrees!) (think sundial)
	float m_azimuth;
	/// angle up and down (degrees!) (think sundial handle)
	float m_polar;

	/// move always, or only on click?
	bool m_on_click;
	/// button to click when onclick turned on
	mouse::button m_btn;

	/// modulo, but for floats
	float fmod(float v, float lo, float hi);

	/// has the mouse been updated yet
	bool m_first_mouse;
};

}
