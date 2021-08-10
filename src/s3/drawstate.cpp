#include "s3/drawstate.hpp"

#include <s3/window.hpp>

namespace s3 {

drawstate::drawstate()
	: transform(),
	  shader(&window::resource().shader()),
	  camera(nullptr),
	  material(nullptr),
	  light(nullptr) {
}

}
