#include "s3/util/time.hpp"

namespace s3::util {

time::time() {
}

time::time(long x)
	: m_dur(x) {
}

time time::minutes(double mins) {
	return time(static_cast<long>(mins * 60 * 1000));
}

time time::seconds(double secs) {
	return time(static_cast<long>(secs * 1000));
}

time time::milliseconds(long ms) {
	return time(ms);
}

double time::as_minutes() const {
	return static_cast<double>(m_dur) / 1000. / 60.;
}

double time::as_seconds() const {
	return static_cast<double>(m_dur) / 1000.;
}

long time::as_milliseconds() const {
	return m_dur;
}

}
