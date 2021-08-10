#include "s3/surfaceable.hpp"

namespace s3 {

surfaceable::surfaceable() {
}

surfaceable::~surfaceable() {
}

s3::material* surfaceable::material() {
	return this;
}

const s3::material* surfaceable::material() const {
	return this;
}

}
