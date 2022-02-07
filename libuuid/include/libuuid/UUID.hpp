#pragma once
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>

// windows includes
#ifdef _WIN32
#pragma comment(lib, "rpcrt4.lib") // UuidCreate - Minimum supported OS Win 2000
#include <iostream>
#include <windows.h>
#endif
// linux includes
#ifdef __linux__
#include <uuid/uuid.h>
#endif

namespace libUUID {
namespace impl {
inline std::string generateUUID() {
	// windows includes
#ifdef _WIN32
	UUID uuid;
	UuidCreate(&uuid);
	char *str;
	UuidToStringA(&uuid, (RPC_CSTR *)&str);
	std::string uuid_str(str);
	RpcStringFreeA((RPC_CSTR *)&str);
	return uuid_str;
#endif
// linux includes
#ifdef __linux__
	uuid_t uuid;
	uuid_generate_random(uuid);
	char uuid_str[37];
	uuid_unparse_lower(uuid, uuid_str);
	return std::string(uuid_str);
#endif
}
} // namespace impl
class UUID {
	std::string m_uuid;

  public:
	/**
	 * @brief Construct a new UUID object with an empty uuid
	 *
	 */
	UUID() = default;
	/**
	 * @brief Construct a new UUID object, doens't check if the uuid is valid
	 *
	 * @param uuid the string representation of the uuid
	 */
	explicit UUID(const std::string &uuid) : m_uuid(uuid) {}

	/**
	 * @brief copy constructor
	 *
	 */
	UUID(const UUID &other) : m_uuid(other.m_uuid){};

	/**
	 * @brief move constructor
	 *
	 */
	UUID(UUID &&other) noexcept : m_uuid(std::move(other.m_uuid)){};

	/**
	 * @brief check if the uuid is valid
	 *
	 * @param uuid the uuid string representation to check
	 * @return true  if the uuid is valid
	 * @return false  if the uuid is invalid
	 */
	static bool is_valid(const std::string &uuid) {
		// version 4 uuid regex
		// ^[0-9a-f]{8}-[0-9a-f]{4}-[0-5][0-9a-f]{3}-[089ab][0-9a-f]{3}-[0-9a-f]{12}$
		static const std::regex regex(
		    "^[0-9a-f]{8}-[0-9a-f]{4}-[0-5][0-9a-f]{3}-["
		    "089ab][0-9a-f]{3}-[0-9a-f]{12}$",
		    std::regex_constants::icase);
		return std::regex_match(uuid, regex);
	}

	/**
	 * @brief generate a new type 4 pseudorandom UUID
	 *
	 * @return UUID the new UUID
	 */
	static UUID generate() {
		// use the platform specific implementation
		return UUID(impl::generateUUID());
	}
	/**
	 * @brief return the UUID from the string
	 *
	 * @param uuid the string representation of the UUID
	 * @return UUID the UUID
	 * @throws std::invalid_argument if the string is not a valid UUID
	 */
	static UUID from_string(const std::string &uuid) {
		UUID uuid_;
		uuid_.m_uuid = uuid;
		// to lower case
		std::transform(uuid_.m_uuid.begin(), uuid_.m_uuid.end(),
		               uuid_.m_uuid.begin(), ::tolower);
		if (!is_valid(uuid_.m_uuid)) {
			throw std::invalid_argument("invalid uuid");
		}
		return uuid_;
	}
	/**
	 * @brief return the string representation of the UUID
	 *
	 * @return std::string the string representation of the UUID
	 */
	const std::string &to_string() const { return m_uuid; }

	/**
	 * @brief check if the UUID is equal to another UUID
	 *
	 * @param other the other UUID
	 * @return true  if the UUIDs are equal
	 * @return false  if the UUIDs are not equal
	 */
	const bool operator==(const UUID &other) const {
		return m_uuid == other.m_uuid;
	}
	/**
	 * @brief check if the UUID is empty
	 *
	 * @return true  if the UUID is empty
	 * @return false  if the UUID is not empty
	 */
	const bool isEmpty() const { return m_uuid.empty(); }

	/**
	 * @brief check if the UUID is valid
	 *
	 * @return true  if the UUIDs is valid
	 * @return false  if the UUIDs is not valid
	 */
	const bool isValid() const { return is_valid(m_uuid); }

	/**
	 * @brief check whether the UUID is not empty and valid
	 *
	 * @return true  if the UUID is not empty and valid
	 * @return false  if the UUID is empty or invalid
	 */
	operator bool() const { return !isEmpty() && isValid(); }

	/**
	 * @brief copy assignment operator
	 *
	 * @param other the UUID to copy
	 * @return UUID& the UUID
	 */
	UUID &operator=(const UUID &other) {
		m_uuid = other.m_uuid;
		return *this;
	}
	/**
	 * @brief move assignment operator
	 *
	 * @param other the UUID to move
	 * @return UUID& the UUID
	 */
	UUID &operator=(UUID &&other) noexcept {
		m_uuid = std::move(other.m_uuid);
		return *this;
	}
};
} // namespace libUUID