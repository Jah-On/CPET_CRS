#include "Member.hpp"
#include <string>

// Constructor
Member::Member(const std::string name, uint8_t credits) {
	this->name        = name;
	this->credits     = credits;
	this->reservation = false;
}

// Accessors
std::string Member::getName() const {
  return name;
}

uint8_t Member::getCredits() const {
    return credits;
}

bool Member::hasReservation() const {
	return reservation;
}

// Mutators
void Member::changeCredits(int8_t amount){
    this->credits += amount;
}

void Member::hasReservation(bool state){
	reservation = state;
}
