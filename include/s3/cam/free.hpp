#pragma once

#include <s3/camera.hpp>
#include <s3/util/clock.hpp>
#include <s3/window.hpp>

#include <glm/glm.hpp>

namespace s3::cams {

/// free first-person style camera
class free : public camera {
public:
	free();
	~free();

	/// updates based on key input
	void update();

	glm::mat4 proj(const rendertarget& target) const;
	glm::mat4 view(const rendertarget& target) const;
	glm::vec3 position() const;

	/// lower values = slower camera turning. default 0.1.
	void set_sens(float sens);
	/// retrieve the mouse sensitivity
	float get_sens() const;

	/// lower values = slower WASD camera acceleration. default 0.35
	void set_accel(float accel);
	/// retrieve the movement acceleration
	float get_accel() const;

	/// lower values = slower WASD maximum movement speed. default 3.0f
	void set_maxvel(float mvel);
	/// retrieve the maximummovement velocity
	float get_maxvel() const;

	/// manually face a direction (angles in degrees)
	void set_dir(float pitch, float yaw);
	/// get the direction we are facing
	glm::vec3 get_dir() const;

	/// manually set the camera's position
	void set_pos(glm::vec3 pos);
	/// retrieve the camera's current position
	glm::vec3 get_pos() const;


private:
	/// clock for measuring deltas between frames
	util::clock m_clock;

	/// camera position
	glm::vec3 m_pos;
	/// camera velocity
	glm::vec3 m_vel;
	/// what is defined as the front of the camera
	glm::vec3 m_facing;
	/// what is considered up
	const glm::vec3 UP = glm::vec3(0, 1.0f, 0);

	/// for hooking into window events
	evt::observer m_ob;

	/// mouse x and y position
	float m_mouse_x, m_mouse_y;
	/// previous mouse x and y position
	float m_mouse_px, m_mouse_py;
	/// mouse pitch and yaw
	float m_mouse_pitch, m_mouse_yaw;
	/// is this the first time the mouse has moved?
	bool m_first_mouse;

	/// using m_facing and m_pos, update pitch and yaw. used primarily for set_pos
	void update_pitch_yaw();

	/* physics variables */
	float m_accel;	 /// acceleration
	float m_sens;	 /// mouse sens
	float m_mvel;	 /// maximum velocity

	/// decelerate a single scalar
	float decel(float v);

	/// vector projection \proj_on{vec}
	static float proj(glm::vec3 vec, glm::vec3 on);

	/// decelerate a vector in a given direction
	glm::vec3 decel(glm::vec3 vec, glm::vec3 dir);

	const int FORWARD_KEY  = GLFW_KEY_W;
	const int BACKWARD_KEY = GLFW_KEY_S;
	const int LEFT_KEY	   = GLFW_KEY_A;
	const int RIGHT_KEY	   = GLFW_KEY_D;
	const int UP_KEY	   = GLFW_KEY_SPACE;
	const int DOWN_KEY	   = GLFW_KEY_LEFT_SHIFT;
};

}
