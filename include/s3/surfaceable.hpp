#pragma once

#include <s3/material.hpp>

namespace s3 {

/// base class describing an object that has a material
class surfaceable : public material {
public:
	surfaceable();
	virtual ~surfaceable();

protected:
	/// for use in draw() to match up with other renderable properties
	s3::material* material();
	const s3::material* material() const;
};

}
