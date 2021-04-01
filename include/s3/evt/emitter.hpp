#pragma once

#include <functional>
#include <unordered_map>

#include <s3/evt/data.hpp>

namespace s3::evt {

class observer;

/// describes an instance that emits arbitrary events to observers
class emitter {
public:
	/// callback type ran for each observer when an event is emitted
	typedef std::function<void(const data& d)> callback;
	/// map of events to their respective hooks, one given to each observer
	typedef std::unordered_map<int, callback> hookmap;

	virtual ~emitter();

	/// emits an event with name evt and relevant data d
	void emit(int evt, data d);

private:
	friend class observer;

	/// called internally by observer to hook into
	void hook(observer& o, int evt, callback c);
	/// remove an entire observer and all its hooks
	void unhook(observer& o);
	/// remove a specific event hook from an observer
	void unhook(observer& o, int evt);

	/// all hooks of all observers
	std::unordered_map<observer*, hookmap> m_hooks;
};

}
