#pragma once

#include <s3/evt/emitter.hpp>

namespace s3::evt {

/// used for hooking into an event emitter. removes all hooks on destruction.
class observer {
public:
	/// construct the observer, attached to a given emitter.
	/// multiple observers can be encapsulated if more than one emitter must be hooked to
	observer(emitter& em);

	/// removes all hooks from the emitter on destruction
	~observer();

	/// hook into an event with the given callback
	void hook(int evt, emitter::callback cb);

	/// unhook from a specific event
	void unhook(int evt);

	/// unhook from all events
	void unhook();

private:
	/// the emitter this observer is attached to
	emitter& m_em;
};

}
