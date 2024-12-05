#include <array>
#include <cstdint>
#include <string>
#include <Member.hpp>

typedef std::array<char, 9> Pin;

enum class ReservationResult {
	SUCCESS,
	ALREADY_TAKEN,
	INVALID_PIN,
	TOO_FEW_CREDITS
};

class Reservation {
public:
	Reservation(uint8_t cost);

	// Modifiers
	ReservationResult take(Member& member);
	ReservationResult drop(Pin&    pin);

	// Accessors
	bool              isTaken()   const;
	std::string       assinedTo() const;
	Pin               getPin()    const;
	uint8_t           getCost()   const;
private:
	void              generatePin();

	uint8_t           cost;
	Member*           assignee;
	Pin               pin;
};
