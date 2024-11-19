#include <cstdint>
#include <optional>
#include <string>
#include "Member.hpp"

enum class ReservationResult {
	SUCCESS,
	ALREADY_TAKEN,
	INVALID_PIN
};

class Reservation {
private:
	uint8_t               cost;
	std::optional<Member> assignee;
public:
	Reservation(uint8_t cost);

	// Modifiers
	ReservationResult take(Member member, std::string pin);
	ReservationResult drop(std::string pin);

	// Accessors
	bool              isTaken();
	std::string       assinedTo();
};
