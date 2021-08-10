#pragma once

#include <s3/drawstate.hpp>
#include <s3/rendertarget.hpp>

namespace s3 {

/// abstract class to describe an object as renderable
class renderable {
public:
	virtual ~renderable();

protected:
	friend class rendertarget;

	/// called by s3::rendertarget::draw to render the object
	virtual void draw(rendertarget& w, drawstate ds) = 0;
};

}
