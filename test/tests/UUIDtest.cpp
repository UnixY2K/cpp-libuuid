#include <libuuid/UUID.hpp>
#include <catch2/catch.hpp>

TEST_CASE("UUID", "[util]") {
	SECTION("generate") {
		auto uuid = libUUID::UUID::generate();
		REQUIRE(libUUID::UUID::is_valid(uuid.to_string()));
	}
}