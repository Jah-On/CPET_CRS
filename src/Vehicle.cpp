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
