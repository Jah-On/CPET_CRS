#include <Vehicle.hpp>

Vehicle::Vehicle(const std::string driver, const VehicleColor color) {
	this->driver = driver;
	this->color  = color;
}

std::string Vehicle::getDriver() const {
  return driver;
}

VehicleColor Vehicle::getColor() const {
  return color;
}

// ReservationResult Vehicle::reserve(Member member, std::string pin){
//     return reservation.take(member, pin);
// }

// ReservationResult Vehicle::cancelReservation(std::string pin){
//     return reservation.drop(pin);
// }

// bool Vehicle::isReserved(){
//     return reservation.isTaken();

// }

// std::string Vehicle::reservedBy(){
//     return reservation.assinedTo();
// }

Pickup::Pickup(const std::string driver, const VehicleColor color) :
	Vehicle(driver, color){}

std::array<Reservation, 1>& Pickup::getReservations() {
	return passengers;
}

Compact::Compact(const std::string driver, const VehicleColor color) :
	Vehicle(driver, color){}

std::array<Reservation, 3>& Compact::getReservations() {
	return passengers;
}

Sedan::Sedan(const std::string driver, const VehicleColor color) :
	Vehicle(driver, color){}

std::array<Reservation, 4>& Sedan::getReservations() {
	return passengers;
}

// // Base Vehicle Class
// Vehicle::Vehicle(std::string driver, VehicleColor color) :
//     driver(driver),
//     color(color) {
// }

// // Pickup Class
// Pickup::Pickup(std::string driver, VehicleColor color) :
//     Vehicle(driver, color) {
// }

// // Compact Class
// Compact::Compact(std::string driver, VehicleColor color) :
//     Vehicle(driver, color) {
// }

// // Sedan Class
// Sedan::Sedan(std::string driver, VehicleColor color) :
//     Vehicle(driver, color) {
// }
