#include "catch2/catch.hpp"

#include <s3.hpp>

TEST_CASE("observer pattern implementation testing", "[emitter]") {
	using namespace s3::evt;

	enum evts {
		add,
		foo,
	};

	emitter em;
	observer* ob = new observer(em);
	int res		 = 0;

	em.emit(add, data().set("by", 5));
	REQUIRE(res == 0);

	ob->hook(add, [&res](const data& d) {
		res += d.get<int>("by");
	});
	REQUIRE(res == 0);

	em.emit(add, data().set("by", 3));
	REQUIRE(res == 3);

	em.emit(add, data().set("by", 1));
	em.emit(add, data().set("by", 1));
	em.emit(add, data().set("by", 1));
	REQUIRE(res == 6);

	em.emit(foo, data().set("by", 1));
	REQUIRE(res == 6);

	ob->unhook(add);
	em.emit(add, data().set("by", 10));
	REQUIRE(res == 6);

	ob->hook(add, [&res](const data& d) {
		res += d.get<int>("by");
	});
	em.emit(add, data().set("by", 10));
	REQUIRE(res == 16);

	ob->unhook();
	em.emit(add, data().set("by", 10));
	REQUIRE(res == 16);

	ob->hook(add, [&res](const data& d) {
		res += d.get<int>("by");
	});
	em.emit(add, data().set("by", 10));
	REQUIRE(res == 26);

	delete ob;

	em.emit(add, data().set("by", 10));
	REQUIRE(res == 26);
}
