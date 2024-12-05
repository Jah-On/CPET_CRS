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
	/*
		Reservation class constructor.

		Parameters:
			uint8_t cost: Sets the number of the points the reservation is worth.
		Returns:
			Class instance.
	*/
	Reservation(uint8_t cost);

	// Modifiers
	/*
		Requests the reservation be taken for a member.

		Parameters:
			Member& member: Reference member to make the request for.
		Returns:
			ReservationResult: Specifies the result of the request.
	*/
	ReservationResult take(Member& member);
	/*
		Requests the reservation be dropped.

		Parameters:
			Pin& pin: Reference Pin to permit (or deny) the request.
		Returns:
			ReservationResult: Specifies the result of the request.
	*/
	ReservationResult drop(Pin&    pin);

	// Accessors
	/*
		Gets whether the reservation is taken.

		Parameters:
		Returns:
			bool: True if a member already has this reservation, otherwise false.
	*/
	bool              isTaken()   const;
	/*
		Gets the names of the person whom the reservation is assigned to.

		Parameters:
		Returns:
			std::string: Name of member or "Unassigned" if not yet taken.
	*/
	std::string       assinedTo() const;
	/*
		Gets the reservation pin.

		Parameters:
		Returns:
			Pin: Pin for the current reservation holder.
	*/
	Pin               getPin()    const;
	/*
		Gets the cost of the reservation.

		Parameters:
		Returns:
			uint8_t: The number of credits the reservation is worth.
	*/
	uint8_t           getCost()   const;
private:
	/*
		Fills "Pin" varible with RNG characters from '0' to '9'.

		Parameters:
		Returns:
	*/
	void              generatePin();

	uint8_t           cost;
	Member*           assignee;
	Pin               pin;
};
