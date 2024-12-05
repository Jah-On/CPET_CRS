#include <Reservation.hpp>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <string>

Reservation::Reservation(uint8_t cost) : cost(cost) {
	assignee = nullptr;
}

ReservationResult Reservation::take(Member& member) {
    if (isTaken()) return ReservationResult::ALREADY_TAKEN;

    if ((member.getCredits() - cost) < 0) return ReservationResult::TOO_FEW_CREDITS;

    assignee = &member;
    assignee->hasReservation(true);
    assignee->changeCredits(-cost);
    generatePin();

    return ReservationResult::SUCCESS;
}

ReservationResult Reservation::drop(Pin& pin) {
    if (!isTaken()) return ReservationResult::SUCCESS;

    for (size_t index = 0; index < pin.size(); ++index){
    	if (pin[index] != this->pin[index]) return ReservationResult::INVALID_PIN;
    }

    assignee->changeCredits(cost); // Refund credits
    assignee->hasReservation(false);
    assignee = nullptr; // Mark as not taken

    return ReservationResult::SUCCESS;
}

bool Reservation::isTaken() const {
    return assignee != nullptr;
}

std::string Reservation::assinedTo() const {
    if (isTaken()) return assignee->getName();

    return "Unassigned";
}

Pin Reservation::getPin() const {
	return pin;
}

uint8_t Reservation::getCost() const {
	return cost;
}

void Reservation::generatePin(){
	std::srand(std::time(nullptr));

	for (char& val : pin) val = '0' + std::rand() / ((RAND_MAX + 1u) / 10);
	pin.back() = 0;
}

// // Constructor
// Reservation::Reservation(const std::string& passengerName,
//     creditCost(creditCost),
//     member(nullptr) {
// }

// // Member Functions

// void Reservation::reserve(Member* member) {
//   this->member = member;
//   member->changeCredits(-static_cast<int8_t>(creditCost));
// }

// void Reservation::cancel() {
//     if (member) {
//         member->changeCredits(static_cast<int8_t>(creditCost));
//         member = nullptr;
//     }
// }

// bool Reservation::isReserved() const {
//   return (member != nullptr);
// }

// Member* Reservation::getMember() const {
//   return member;
// }

// uint8_t Reservation::getCreditCost() const {
//   return creditCost;
// }
