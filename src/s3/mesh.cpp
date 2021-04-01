#include "s3/mesh.hpp"

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

void mesh::del() {
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteVertexArrays(1, &m_vao);
}

void mesh::clear() {
	m_v.clear();
	m_e.clear();

	bind();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
}

//TODO: this
void mesh::load_from_obj(std::istream& data) {
	clear();
	for (std::string line; std::getline(data, line);) {
		std::istringstream ln(line);
		std::string start;
		ln >> start;
	}
}
void mesh::load_from_obj(const std::string& data) {
	std::istringstream datastream(data);
	return load_from_obj(datastream);
}

void mesh::push_v(vertex v) {
	m_v.push_back(v);
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

void mesh::draw() {
	bind();
	glDrawElements(m_prim, m_e.size(), GL_UNSIGNED_INT, nullptr);
}

void mesh::bind() {
	glBindVertexArray(m_vao);
}
}
