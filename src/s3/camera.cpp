#include "s3/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace s3 {

camera::camera() {
}

camera::~camera() {
}

glm::mat4 camera::proj() const {
	return glm::perspective(glm::radians(45.f),
							window().size().x / window().size().y,
							0.1f, 100.f);
}

glm::mat4 camera::view() const {
	return glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}

void camera::update() {
}

s3::window& camera::window() const {
	return window::active();
}

}
