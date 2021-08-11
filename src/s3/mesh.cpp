#include "s3/mesh.hpp"

#include <algorithm>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <stdexcept>

namespace s3 {

mesh::mesh()
	: m_prim(primitive::TRIANGLES) {
	glGenVertexArrays(1, &m_vao);
	bind();

	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	clear();
}

mesh::~mesh() {
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteVertexArrays(1, &m_vao);
}

void mesh::clear() {
	m_v.clear();
	m_e.clear();
	m_materials.clear();

	bind();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
}

void mesh::set_primitive_type(primitive p) {
	m_prim = p;
}

primitive mesh::get_primitive_type() const {
	return m_prim;
}

/// reads in position, uv, and norm data from a .obj format face specifier
static void read_face(std::string s, int& i, int& t, int& n) {
	std::transform(s.begin(), s.end(), s.begin(), [](const char& c) {
		if (c == '/') {
			return ' ';
		} else {
			return c;
		}
	});
	std::istringstream is(s);
	is >> i >> t >> n;
	i -= 1;
	t -= 1;
	n -= 1;
}

void mesh::load_from_obj(std::istream& data) {
	clear();
	std::vector<glm::vec3> v_pos;
	std::vector<glm::vec2> v_tex;
	std::vector<glm::vec3> v_norm;
	for (std::string line; std::getline(data, line);) {
		std::istringstream ln(line);
		std::string start;
		ln >> start;
		if (start == "v") {
			float x, y, z;
			ln >> x >> y >> z;
			v_pos.push_back(glm::vec3(x, y, z));
		} else if (start == "vt") {
			float u, v;
			ln >> u >> v;
			v_tex.push_back(glm::vec2(u, v));
		} else if (start == "vn") {
			float x, y, z;
			ln >> x >> y >> z;
			v_norm.push_back(glm::vec3(x, y, z));
		} else if (start == "f") {
			std::string a, b, c;
			ln >> a >> b >> c;
			int i, t, n;   // tex, norm
			vertex v1, v2, v3;
			read_face(a, i, t, n);
			v1.pos	= v_pos[i];
			v1.uv	= v_tex[t];
			v1.norm = v_norm[n];
			read_face(b, i, t, n);
			v2.pos	= v_pos[i];
			v2.uv	= v_tex[t];
			v2.norm = v_norm[n];
			read_face(c, i, t, n);
			v3.pos	= v_pos[i];
			v3.uv	= v_tex[t];
			v3.norm = v_norm[n];

			int vi1, vi2, vi3;
			vi1 = push_v(v1);
			vi2 = push_v(v2);
			vi3 = push_v(v3);
			push_t(vi1, vi2, vi3);
		} else if (start == "mtllib") {
			std::string path;
			ln >> path;
			load_mtl_library(path);
		} else if (start == "usemtl") {
			std::string mtl_name;
			ln >> mtl_name;
			*material() = m_materials[mtl_name];
		}
	}
	gen();
}

void mesh::load_from_obj(const std::string& data) {
	std::istringstream datastream(data);
	return load_from_obj(datastream);
}

void mesh::load_from_file(const std::string& file) {
	std::ifstream f(file);
	if (!f) {
		throw std::runtime_error("Could not open file " + file);
	}
	load_from_obj(f);
	f.close();
}

void mesh::load_mtl_library(const std::string& path) {
	std::ifstream f(path);
	if (!f) {
		throw std::runtime_error("Could not open file " + path);
	}
	std::string current_mtl_name = "";	 // currently worked on material
	s3::material current_mtl;
	for (std::string line; std::getline(f, line);) {
		std::istringstream ln(line);
		std::string start;
		ln >> start;
		if (start == "newmtl") {
			if (!current_mtl_name.empty()) {
				m_materials[current_mtl_name] = current_mtl;
				current_mtl.clear();
				current_mtl_name.clear();
			}
			ln >> current_mtl_name;
		} else if (start == "Ns") {
			float shininess;
			ln >> shininess;
			current_mtl.set_shininess(shininess);
		} else if (start == "map_Kd") {
			std::string diffuse_path;
			ln >> diffuse_path;
			current_mtl.set_diffuse(s3::window::resource().texture(diffuse_path));
		} else if (start == "map_Ns") {
			std::string specular_path;
			ln >> specular_path;
			current_mtl.set_specular(s3::window::resource().texture(specular_path));
		} else if (start == "map_Ke") {
			std::string emission_path;
			ln >> emission_path;
			current_mtl.set_emission(s3::window::resource().texture(emission_path));
		}
	}
	m_materials[current_mtl_name] = current_mtl;
	f.close();
}

int mesh::push_v(vertex v) {
	m_v.push_back(v);
	return size() - 1;
}

void mesh::push_t(unsigned a, unsigned b, unsigned c) {
	m_e.push_back(a);
	m_e.push_back(b);
	m_e.push_back(c);
}

void mesh::gen() {
	bind();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_v.size() * sizeof(vertex), m_v.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_e.size() * sizeof(unsigned int), m_e.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
						  sizeof(vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
						  sizeof(vertex), (void*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
						  sizeof(vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

int mesh::size() const {
	return m_v.size();
}

void mesh::draw(rendertarget& target, drawstate ds) {
	//! prioritize drawstate material, shaders, etc. over this object's settings

	target.bind();

	ds.transform *= transform();

	if (ds.shader) {
		ds.shader->use();
	} else {
		throw std::runtime_error("Cannot render without a shader!");
	}
	if (ds.camera) {
		ds.camera->update();
		ds.shader->set_uniform("view", ds.camera->view(target));
		ds.shader->set_uniform("proj", ds.camera->proj(target));
		ds.shader->set_uniform("cam", ds.camera->position());
	} else {
		throw std::runtime_error("Cannot render without a camera!");
	}
	if (ds.material) {
		ds.material->populate("material", *ds.shader);
	} else if (material()) {
		material()->populate("material", *ds.shader);
	} else {
		s3::material().populate("material", *ds.shader);
	}
	if (ds.light) {
		ds.light->populate("light", *ds.shader);
	} else {
		light::light().populate("light", *ds.shader);
	}

	glm::mat4 model = ds.transform.matrix();
	ds.shader->set_uniform("model", model);
	ds.shader->set_uniform("norm_model", glm::mat3(glm::transpose(glm::inverse(model))));

	gl_draw();
}

void mesh::gl_draw() {
	bind();
	glDrawElements(m_prim, m_e.size(), GL_UNSIGNED_INT, nullptr);
}

void mesh::bind() {
	glBindVertexArray(m_vao);
}
}
