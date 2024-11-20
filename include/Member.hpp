#include <cstddef>
#include <cstdint>
#include <string>

class Member {
public:
	// Constructor
	Member(std::string name, std::string pin, uint8_t credits);

	// Accessors
	std::string getName();

	// Mutators
	void changeCredits(int8_t amount);

	bool validatePin(std::string& pin);
private:
	std::string name;
	size_t      pinHash;
	uint8_t     credits;
};
