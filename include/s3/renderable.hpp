#pragma once

#include <s3/drawstate.hpp>
#include <s3/transformable.hpp>
#include <s3/window.hpp>

namespace s3 {

/// abstract class to describe an object as renderable
class renderable : public transformable {
public:
	virtual ~renderable();

protected:
	friend class window;

	/// called by s3::window::draw to render the object
	virtual void draw(window& w, drawstate ds);
};

}
