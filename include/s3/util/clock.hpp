#pragma once

#include <s3/util/time.hpp>

namespace s3::util {

/// clock for measuring elapsed time
class clock {
public:
	/// start the clock
	clock();

	/// restart the clock, returning the time since last restart
	time restart();
	/// check how much time has elapsed without restarting the clock
	time elapsed() const;

private:
	/// time point since the last time the clock was restarted
	std::chrono::time_point<std::chrono::system_clock> m_last;
};

}
