#include <cstdint>
#include <string>

class Member {
public:
	// Constructor
	/*
		Member class constructor.

		Parameters:
			std::string name: Sets the name of the member.
			uint8_t credits: Sets the number of credits the member has.
		Returns:
			Class instance.
	*/
	Member(std::string name, uint8_t credits);

	// Accessors
	/*
		Gets the member's name.

		Parameters:
		Returns:
			std::string: Name of the member.
	*/
	std::string getName()        const;
	/*
		Gets the number of credits the member has.

		Parameters:
		Returns:
			uint8_t: Number of credits the user has.
	*/
	uint8_t     getCredits()     const;
	/*
		Gets the member's reservation status.

		Parameters:
		Returns:
			bool: True if the user has a reservation, false otherwise.
	*/
	bool        hasReservation() const;

	// Mutators
	/*
		Changes the member's credits by a given amount.

		Parameters:
			int8_t: The amount to change the credits by, positive or negative.
		Returns:
	*/
	void changeCredits(int8_t amount);
	/*
		Sets the member's reservation status.

		Parameters:
			bool: Set to true if the user has a reservation, false otherwise.
		Returns:
	*/
	void hasReservation(bool state);
private:
	std::string name;
	uint8_t     credits;
	bool        reservation;
};
