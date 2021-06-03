#pragma once

#include <glm/glm.hpp>
#include <s3/window.hpp>

namespace s3 {

/// abstract camera api for passing to the window and updating projection and view models
class camera {
public:
	camera();
	virtual ~camera();

	/// returns a custom projection matrix based on the camera's settings
	virtual glm::mat4 proj() const;
	/// returns a custom view matrix based on the camera's projection settings
	virtual glm::mat4 view() const;

	/// useful for updating, i.e. moving the camera based on input
	virtual void update();

protected:
	/// returns a reference to the primary app window
	s3::window& window() const;
};

}
