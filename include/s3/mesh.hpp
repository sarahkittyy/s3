#pragma once

#include <GL/glew.h>
#include <s3/vertex.hpp>
#include <string>
#include <vector>

namespace s3 {

enum primitive {
	POINTS		  = GL_POINTS,
	LINES		  = GL_LINES,
	LINESTRIP	  = GL_LINE_STRIP,
	LINELOOP	  = GL_LINE_LOOP,
	TRIANGLES	  = GL_TRIANGLES,
	TRIANGLESTRIP = GL_TRIANGLE_STRIP,
	TRIANGLEFAN	  = GL_TRIANGLE_FAN,
};


/// mesh for holding 3d vertex data
class mesh {
public:
	mesh();

	/// delete internal opengl vertex data
	void del();

	mesh(const mesh&) = delete;
	mesh& operator=(const mesh&) = delete;

	/// clear the entire mesh of all vertices
	void clear();

	/// load the mesh data from a OBJ formatted model
	void load_from_obj(std::istream& data);
	void load_from_obj(const std::string& data);

	/// append a vertex to the mesh
	void push_v(vertex v);

	/// append a triangle to the mesh (counter clockwise!)
	void push_t(unsigned a, unsigned b, unsigned c);

	/// flush vertices and generate the opengl mesh data
	void gen();

	/// count how many vertices are in this mesh
	int size() const;

	/// render the mesh
	void draw();

private:
	std::vector<vertex> m_v;		 /// stored vertices
	std::vector<unsigned int> m_e;	 /// stored element indices
	primitive m_prim;				 /// primitive type

	GLuint m_vao;	/// primary vertex array
	GLuint m_ebo;	/// element buffer object
	GLuint m_vbo;	/// buffer for vertex data

	void bind();   /// bind the vertex array as active
};

}
