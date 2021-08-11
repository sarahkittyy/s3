#include "s3/color.hpp"

namespace s3 {

color::color()
	: r(0), g(0), b(0), a(255) {
}

color::color(float r, float g, float b, float a)
	: r(r), g(g), b(b), a(a) {
}

color color::grey_norm(float c, float a) {
	return color(c, c, c, a);
}

color color::grey_int(int c, int a) {
	return color(c / 255.f, c / 255.f, c / 255.f, a / 255.f);
}

color color::from_ints(int r, int g, int b, int a) {
	return color(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

color color::from_ints(glm::vec4 v) {
	return color(v.r / 255.f, v.g / 255.f, v.b / 255.f, v.a / 255.f);
}

color color::from_ints(glm::vec3 v) {
	return color(v.r / 255.f, v.g / 255.f, v.b / 255.f, 1.0f);
}

color color::from_norm(float r, float g, float b, float a) {
	return color(r, g, b, a);
}

color color::from_norm(glm::vec4 v) {
	return color(v.r, v.g, v.b, v.a);
}

color color::from_norm(glm::vec3 v) {
	return color(v.r, v.g, v.b, 1.0f);
}

color::operator glm::vec4() const {
	return glm::vec4(r, g, b, a);
}

color::operator glm::vec3() const {
	return glm::vec3(r, g, b);
}

}
