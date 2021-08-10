#pragma once

#include <s3/camera.hpp>
#include <s3/material.hpp>
#include <s3/shader.hpp>
#include <s3/transform.hpp>

#include <s3/light/light.hpp>

namespace s3 {

class shader;
class camera;

/// stores the state of a render (shader, texture, etc)
class drawstate {
public:
	drawstate();

	/// transform to be used as the model matrix in the defualt shader
	s3::transform transform;
	/// shader to render this object with
	s3::shader* shader;
	/// camera to use
	s3::camera* camera;
	/// material to use
	const s3::material* material;
	/// light source
	const s3::light::light* light;
};

}
