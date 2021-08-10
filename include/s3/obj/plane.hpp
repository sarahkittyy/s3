#pragma once

#include <s3/mesh.hpp>
#include <s3/renderable.hpp>
#include <s3/texturable.hpp>
#include <s3/transformable.hpp>

#include <glm/glm.hpp>

namespace s3::obj {

/// a simple 2d rectangular plane parallel to the x-z axis
class plane : public renderable, public transformable, public texturable {
public:
	/// construct the plane given the top left coord and size
	plane(glm::vec3 top_left, glm::vec2 size);

private:
	void draw(rendertarget& target, drawstate ds);

	/// internal plane mesh
	s3::mesh m_mesh;

	/// plane specs
	glm::vec3 m_tl;
	glm::vec2 m_sz;

	/// internally compute the mesh
	void mesh_compute();
};

}
