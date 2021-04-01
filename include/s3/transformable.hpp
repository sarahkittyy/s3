#pragma once

#include <s3/transform.hpp>

namespace s3 {

/// abstract class, derived by renderable, allows an object to control its global transform
class transformable {
public:
	/// retrieve the internal transform
	s3::transform& transform();

private:
	s3::transform m_tf; /// internally stored transform object
};

}
