#include <cstdint>
#include <string>

class Member {
public:
	// Constructor
	Member(std::string name, uint8_t credits);

	// Accessors
	std::string getName()        const;
	uint8_t     getCredits()     const;
	bool        hasReservation() const;

	// Mutators
	void changeCredits(int8_t amount);
	void hasReservation(bool state);
private:
	std::string name;
	uint8_t     credits;
	bool        reservation;
};
