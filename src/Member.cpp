#include "Member.hpp"
#include <iostream>
#include <string>

// Constructor
Member::Member(const std::string name, uint8_t credits) {
	this->name    = name;
	this->credits = credits;
}

// Accessors
std::string Member::getName() const {
  return name;
}

uint8_t Member::getCredits(){
    return credits;
}

// Mutators
void Member::changeCredits(int8_t amount){
    this->credits += amount;
}
