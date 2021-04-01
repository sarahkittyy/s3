#include "s3/evt/observer.hpp"

#include <s3/evt/emitter.hpp>

namespace s3::evt {

observer::observer(emitter& em)
	: m_em(em) {
}

observer::~observer() {
	unhook();
}

void observer::hook(int evt, emitter::callback cb) {
	m_em.hook(*this, evt, cb);
}

void observer::unhook(int evt) {
	m_em.unhook(*this, evt);
}

void observer::unhook() {
	m_em.unhook(*this);
}

}
