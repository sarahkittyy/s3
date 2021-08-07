#pragma once

#include <s3/drawstate.hpp>
#include <s3/transformable.hpp>

namespace s3 {

class rendertarget;

/// abstract class to describe an object as renderable
class renderable : public transformable {
public:
	virtual ~renderable();

protected:
	friend class rendertarget;

	/// called by s3::rendertarget::draw to render the object
	virtual void draw(rendertarget& w, drawstate ds) = 0;
};

}
