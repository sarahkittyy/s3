#include "s3/evt/emitter.hpp"

#include <s3/evt/observer.hpp>

namespace s3::evt {

emitter::~emitter() {
}

void emitter::emit(int evt, data d) {
	if (m_hooks.empty()) return;

	for (auto& [ob, hm] : m_hooks) {
		for (auto& [cb_evt, cb] : hm) {
			if (cb_evt == evt) {
				cb(d);
			}
		}
	}
}

void emitter::hook(observer& o, int evt, callback c) {
	m_hooks[&o][evt] = c;
}

void emitter::unhook(observer& o) {
	m_hooks.erase(&o);
}

void emitter::unhook(observer& o, int evt) {
	m_hooks[&o].erase(evt);
}

}
