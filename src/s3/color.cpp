#include "s3/color.hpp"

namespace s3 {

color::color()
	: r(0), g(0), b(0), a(255) {
}

color::color(float r, float g, float b, float a)
	: r(r), g(g), b(b), a(a) {
}

color color::from_ints(int r, int g, int b, int a) {
	return color(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

color color::from_norm(float r, float g, float b, float a) {
	return color(r, g, b, a);
}

}
