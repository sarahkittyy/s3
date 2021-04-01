#pragma once

#include <s3/shader.hpp>
#include <s3/texture.hpp>
#include <s3/transform.hpp>

namespace s3 {

/// stores the state of a render (shader, texture, etc)
class drawstate {
public:
	drawstate();

	/// default, empty draw state
	static drawstate empty;

	/// transform to be used as the model matrix in the defualt shader
	s3::transform transform;
	/// texture to be bound on render
	s3::texture* texture;
	/// shader to render this object with
	s3::shader* shader;
};

}
