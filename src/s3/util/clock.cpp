#include "s3/util/clock.hpp"

namespace s3::util {

clock::clock() {
	restart();
}

time clock::restart() {
	time t = elapsed();
	m_last = std::chrono::system_clock::now();
	return t;
}

time clock::elapsed() const {
	auto now = std::chrono::system_clock::now();
	auto ms	 = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_last);
	return time::milliseconds(ms.count());
}

}
