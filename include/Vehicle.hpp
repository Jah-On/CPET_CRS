#include <array>
#include <Reservation.hpp>
#include <cmath>
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
public:
	Vehicle(std::string driver, VehicleColor color);

	// Accessors
	std::string  getDriver();
	VehicleColor getColor();
private:
	std::string  driver;
	VehicleColor color;
};

class Pickup : public Vehicle {
public:
	Pickup(std::string driver, VehicleColor color);
private:
	std::array<Reservation, 1> passengers = {
		Reservation(5)
	};
};

class Compact : public Vehicle {
public:
	Compact(std::string driver, VehicleColor color);
private:
	std::array<Reservation, 3> passengers = {
		Reservation(5), Reservation(3), Reservation(3)
	};
};

class Sedan : public Vehicle {
public:
	Sedan(std::string driver, VehicleColor color);
private:
	std::array<Reservation, 4> passengers = {
		Reservation(5), Reservation(2), Reservation(1), Reservation(2)
	};
};
