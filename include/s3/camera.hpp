#pragma once

#include <glm/glm.hpp>

namespace s3 {

class window;
class rendertarget;

/// abstract camera api for passing to the window and updating projection and view models
class camera {
public:
	camera();
	virtual ~camera();

	/// returns a custom projection matrix based on the camera's settings
	virtual glm::mat4 proj(const rendertarget& target) const;
	/// returns a custom view matrix based on the camera's projection settings
	virtual glm::mat4 view(const rendertarget& target) const;

	/// retrieve the camera's position
	virtual glm::vec3 position() const;

	/// useful for updating, i.e. moving the camera based on input
	virtual void update();

protected:
	/// returns a reference to the primary app window
	s3::window& window() const;
};

}
