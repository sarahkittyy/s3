#include "s3/obj/plane.hpp"

namespace s3::obj {

plane::plane(glm::vec3 top_left, glm::vec2 size)
	: m_tl(top_left),
	  m_sz(size) {
	mesh_compute();
}

void plane::draw(rendertarget& target, drawstate ds) {
	ds.transform *= transform();
	ds.material = material();
	target.draw(m_mesh, ds);
}

void plane::mesh_compute() {
	m_mesh.clear();

	// four points of the plane
	s3::vertex a, b, c, d;
	a.pos = m_tl;
	b.pos = glm::vec3(m_tl.x, m_tl.y, m_tl.z + m_sz.y);
	c.pos = glm::vec3(m_tl.x + m_sz.x, m_tl.y, m_tl.z + m_sz.y);
	d.pos = glm::vec3(m_tl.x + m_sz.x, m_tl.y, m_tl.z);

	// normal
	glm::vec3 norm = glm::vec3(0, 1, 0);
	a.norm		   = norm;
	b.norm		   = norm;
	c.norm		   = norm;
	d.norm		   = norm;

	// uvs
	a.uv = glm::vec2(0, 0);
	b.uv = glm::vec2(0, 1);
	c.uv = glm::vec2(1, 1);
	d.uv = glm::vec2(1, 0);

	m_mesh.push_v(a);
	m_mesh.push_v(b);
	m_mesh.push_v(c);
	m_mesh.push_v(d);

	m_mesh.push_t(0, 1, 2);
	m_mesh.push_t(0, 2, 3);

	m_mesh.gen();
}

}
