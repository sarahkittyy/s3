#include "s3/drawstate.hpp"

namespace s3 {

drawstate drawstate::empty = drawstate();

drawstate::drawstate()
	: transform(),
	  texture(nullptr),
	  shader(nullptr),
	  camera(nullptr) {
}

}
