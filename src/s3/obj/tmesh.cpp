#include "s3/obj/tmesh.hpp"

namespace s3::obj {

void tmesh::draw(rendertarget& target, drawstate ds) {
	ds.texture = texture();
	ds.transform *= transform();
	target.draw((mesh&)(*this), ds);
}

}
