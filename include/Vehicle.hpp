#include <array>
#include "Reservation.hpp"
#include <string>

enum class VehicleColor {
	WHITE,
	BLACK,
	YELLOW,
	GREEN,
	RED,
	BLUE,
	ORANGE,
	PURPLE,
	SILVER,
	GRAY
};

class Vehicle {
private:
	std::string  driver;
	VehicleColor color;
public:
	Vehicle(std::string driver, VehicleColor color);

	// Accessors
	std::string  getDriver();
	VehicleColor getColor();
};

class Pickup : public Vehicle {
	std::array<Reservation, 1> passengers = {
		Reservation(5)
	};
};

class Compact : public Vehicle {
	std::array<Reservation, 3> passengers = {
		Reservation(5), Reservation(3), Reservation(3)
	};
};

class Sedan : public Vehicle {
	std::array<Reservation, 4> passengers = {
		Reservation(5), Reservation(2), Reservation(1), Reservation(2)
	};
};
