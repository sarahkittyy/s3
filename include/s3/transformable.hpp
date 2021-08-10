#pragma once

#include <s3/transform.hpp>

namespace s3 {

/// abstract class, derived by renderable, allows an object to control its global transform
class transformable : public transform {
public:
	/// retrieve the internal transform
	s3::transform& transform();
};

}
