#include "s3/transformable.hpp"

namespace s3 {

s3::transform& transformable::transform() {
	return *this;
}

}
