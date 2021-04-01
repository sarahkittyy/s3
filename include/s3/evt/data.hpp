#pragma once

#include <any>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace s3::evt {

/// stores arbitrary event data
class data {
public:
	/// set a key to a given value
	data& set(std::string k, std::any v);

	/// retrieve a value as type T given key k
	template <typename T>
	T get(std::string k) const {
		try {
			return std::any_cast<T>(getr(k));
		} catch (std::bad_any_cast& e) {
			throw std::runtime_error("Key " + k + " type mismatch.");
		}
	}

	/// checks if a key exists in this data
	bool has(std::string k) const;

	/// check if a key's value is of the given type
	template <typename T>
	bool is(std::string k) const {
		try {
			std::any_cast<T>(getr(k));
			return true;
		} catch (std::bad_any_cast& e) {
			return false;
		}
	}

private:
	/// all internally stored key-value pairs
	std::unordered_map<std::string, std::any> m_data;
	/// retrieve a value by its key
	std::any getr(std::string k) const;
};

}
