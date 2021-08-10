#pragma once

#include <s3/shader.hpp>

#include <sstream>

namespace s3 {

class shader;

/// base class with properties that allow it to be passed into a shader uniform
class uniformstruct {
public:
	uniformstruct();
	virtual ~uniformstruct();

	/// populate the shader with all fields of the struct, given the struct instance name (context)
	virtual void populate(const char* context, shader& s) const;

protected:
	/// fill the field given the context, name, shader, and value
	template <typename T>
	void fill(const char* context, const char* name, const T& data, shader& s) const {
		std::ostringstream ss;
		ss << context;
		ss << ".";
		ss << name;
		s.set_uniform(ss.str().c_str(), data);
	}
};

}
