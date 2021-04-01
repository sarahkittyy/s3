#include "catch2/catch.hpp"

#include <s3.hpp>

#include <thread>

TEST_CASE("clock / timing implementation", "[clock]") {
	using Catch::Generators::random;
	using Catch::Generators::take;
	using s3::util::clock;
	using s3::util::time;

	SECTION("time casting") {
		double secs = GENERATE(take(100, random(0.5f, 20.f)));
		time t		= time::seconds(secs);
		REQUIRE(t.as_seconds() - secs < 0.01);
		REQUIRE(t.as_milliseconds() - (secs * 1000) < 0.01);
		REQUIRE(t.as_minutes() - (secs / 60.0) < 0.01);
	}

	SECTION("clock timing") {
		clock c;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		REQUIRE(c.restart().as_seconds() - 1 < 0.01);
	}
}
