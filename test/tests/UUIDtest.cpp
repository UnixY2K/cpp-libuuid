#include <catch2/catch.hpp>
#include <libuuid/UUID.hpp>

using UUID = libUUID::UUID;

TEST_CASE("UUID", "[util]") {
	SECTION("generate") {
		auto uuid = UUID::generate();
		REQUIRE(uuid);
	}
	SECTION("copy constructor") {
		auto uuid = UUID::generate();
		auto uuid_copy = uuid;
		REQUIRE(uuid_copy.to_string() == uuid.to_string());
	}
	SECTION("move constructor") {
		auto uuid = UUID::generate();
		auto uuid_move = std::move(uuid);
		REQUIRE(uuid.isEmpty());
		REQUIRE(!uuid_move.isEmpty());
	}
	SECTION("copy assignment") {
		auto uuid = UUID::generate();
		UUID uuid_copy;
		uuid_copy = uuid;
		REQUIRE(uuid_copy.to_string() == uuid.to_string());
	}
	SECTION("move assignment") {
		auto uuid = libUUID::UUID::generate();
		UUID uuid_move;
		uuid_move = std::move(uuid);
		REQUIRE(uuid.isEmpty());
		REQUIRE(!uuid_move.isEmpty());
	}
	SECTION("equality") {
		auto uuid = UUID::generate();
		auto uuid_copy = uuid;
		REQUIRE(uuid_copy == uuid);
	}
	SECTION("isEmpty") {
		auto uuid = UUID::generate();
		REQUIRE(!uuid.isEmpty());
	}
	SECTION("isValid") {
		auto uuid = UUID::generate();
		REQUIRE(uuid.isValid());
	}
	SECTION("operator bool") {
		auto uuid = UUID::generate();
		REQUIRE(uuid);
	}
}