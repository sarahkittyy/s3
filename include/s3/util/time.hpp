#pragma once

#include <chrono>

namespace s3::util {

/// stores a duration of time
class time {
public:
	/// initializes an empty (0s duration) time interval
	time();

	/// initialize from minutes
	static time minutes(double mins);
	/// initialize from seconds
	static time seconds(double secs);
	/// initialize from milliseconds
	static time milliseconds(long ms);

	/// return this duration as minutes
	double as_minutes() const;
	/// return this duration as seconds
	double as_seconds() const;
	/// return this duration as milliseconds
	long as_milliseconds() const;

private:
	/// used for static initialization methods, accepts milliseconds
	time(long x);

	/// internally stored duration
	long m_dur;
};

}
