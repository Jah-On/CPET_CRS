#include <array>
#include <Reservation.hpp>
#include <cmath>
#include <string>

enum class VehicleColor {
	BLACK,
	YELLOW,
	GREEN,
	RED,
	BLUE,
	PURPLE
};

class Vehicle {
public:
	/*
		Vehicle class constructor. All child ones have the same constructor.

		Parameters:
			std::string driver: Names the person who owns the vehicle.
			VehicleColor color: Sets the vehicle's color from the VehicleColor enum.
		Returns:
			Class instance.
	*/
	Vehicle(std::string driver, VehicleColor color);

	// Accessors
	/*
		Gets the driver's name.

		Parameters:
		Returns:
			std::string: The driver's name.
	*/
	std::string  getDriver() const;
	/*
		Gets the vehicles's color.

		Parameters:
		Returns:
			VehicleColor: The vehicle's color.
	*/
	VehicleColor getColor()  const;
private:
	std::string  driver;
	VehicleColor color;
};

class Pickup : public Vehicle {
public:
	Pickup(std::string driver, VehicleColor color);

	std::array<Reservation, 1>& getReservations();
private:
	std::array<Reservation, 1> passengers = {
		Reservation(5)
	};
};

class Compact : public Vehicle {
public:
	Compact(std::string driver, VehicleColor color);

	std::array<Reservation, 3>& getReservations();
private:
	std::array<Reservation, 3> passengers = {
		Reservation(5), Reservation(3), Reservation(3)
	};
};

class Sedan : public Vehicle {
public:
	Sedan(std::string driver, VehicleColor color);

	std::array<Reservation, 4>& getReservations();
private:
	std::array<Reservation, 4> passengers = {
		Reservation(5), Reservation(2), Reservation(1), Reservation(2)
	};
};
