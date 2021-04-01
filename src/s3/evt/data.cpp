#include "s3/evt/data.hpp"

namespace s3::evt {

data& data::set(std::string k, std::any v) {
	m_data[k] = v;
	return *this;
}

std::any data::getr(std::string k) const {
	if (!m_data.contains(k)) {
		throw std::runtime_error("Could not find key " + k + ".");
	}

	return m_data.at(k);
}

bool data::has(std::string k) const {
	return m_data.contains(k);
}

}
