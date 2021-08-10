#pragma once

#include <s3/mesh.hpp>
#include <s3/renderable.hpp>
#include <s3/texturable.hpp>
#include <s3/transformable.hpp>

namespace s3::obj {

/// mesh that is renderable, transformable, and texturable
class tmesh : public renderable, public transformable, public texturable, public mesh {
private:
	void draw(rendertarget& target, drawstate ds);
};

}
