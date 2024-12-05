#include "imgui.h"
#include <GUI/GUI.hpp>
#include <fstream>
#include <string>

template<> void GUI::exportVehicle<Pickup>(
	Pickup& vehicle,
	std::string title,
	std::string file,
	std::ofstream* open
){
	std::ofstream* output;
	if (open != NULL) output = open;
	else output = new std::ofstream(file);

	if (open == NULL && !output->is_open()){
		popupMessage = "Could not save file.";
		popupState   = MESSAGE;
		return;
	}

	*output << title << ":" << std::endl;
	*output << "\tDriver: " << vehicle.getDriver() << std::endl;

	for (Reservation& seat : vehicle.getReservations()){
		switch (seat.getCost()) {
		default:
			*output << "\tFront Passenger: " << seat.assinedTo() << std::endl;
			break;
		}
	}

	*output << std::endl;

	if (open == NULL){
		output->close();
		popupMessage = "File saved successfully.";
		popupState   = MESSAGE;
	}
}

template<> void GUI::exportVehicle<Compact>(
	Compact& vehicle,
	std::string title,
	std::string file,
	std::ofstream* open
){
	std::ofstream* output;
	if (open != NULL) output = open;
	else output = new std::ofstream(file);

	if (open == NULL && !output->is_open()){
		popupMessage = "Could not save file.";
		popupState   = MESSAGE;
		return;
	}

	*output << title << ":" << std::endl;
	*output << "\tDriver: " << vehicle.getDriver() << std::endl;

	for (Reservation& seat : vehicle.getReservations()){
		switch (seat.getCost()) {
		case 3:
			*output << "\tBack Seat Passenger: " << seat.assinedTo() << std::endl;
			break;
		default:
			*output << "\tFront Passenger: " << seat.assinedTo() << std::endl;
			break;
		}
	}

	*output << std::endl;

	if (open == NULL){
		output->close();
		popupMessage = "File saved successfully.";
		popupState   = MESSAGE;
	}
}

template<> void GUI::exportVehicle<Sedan>(
	Sedan& vehicle,
	std::string title,
	std::string file,
	std::ofstream* open
){
	std::ofstream* output;
	if (open != NULL) output = open;
	else output = new std::ofstream(file);

	if (open == NULL && !output->is_open()){
		popupMessage = "Could not save file.";
		popupState   = MESSAGE;
		return;
	}

	*output << title << ":" << std::endl;
	*output << "\tDriver: " << vehicle.getDriver() << std::endl;

	for (Reservation& seat : vehicle.getReservations()){
		switch (seat.getCost()) {
		case 1:
			*output << "\tBack Seat Middle Passenger: " << seat.assinedTo() << std::endl;
			break;
		case 2:
			*output << "\tBack Seat Door Passenger: " << seat.assinedTo() << std::endl;
			break;
		default:
			*output << "\tFront Passenger: " << seat.assinedTo() << std::endl;
			break;
		}
	}

	*output << std::endl;

	if (open == NULL){
		output->close();
		popupMessage = "File saved successfully.";
		popupState   = MESSAGE;
	}
}

void GUI::exportAll(){
	std::ofstream file("all_reservations.txt");

	if (!file.is_open()){
		popupMessage = "Could not save file.";
		popupState   = MESSAGE;
		return;
	}

	exportVehicle(pickups[0], "Purple Pickup Truck", "purple_pickup.txt", &file);
	exportVehicle(pickups[1], "Green Pickup Truck", "green_pickup.txt", &file);
	exportVehicle(pickups[2], "Black Pickup Truck", "black_pickup.txt", &file);
	exportVehicle(compacts[0], "Red Compact Car", "red_compact.txt", &file);
	exportVehicle(compacts[1], "Blue Compact Car", "blue_compact.txt", &file);
	exportVehicle(compacts[2], "Yellow Compact Car", "yellow_compact.txt", &file);
	exportVehicle(sedans[0], "Blue Sedan", "blue_sedan.txt", &file);
	exportVehicle(sedans[1], "Black Sedan", "black_sedan.txt", &file);
	exportVehicle(sedans[2], "Green Sedan", "green_sedan.txt", &file);

	file.close();

	popupMessage = "File saved successfully.";
	popupState   = MESSAGE;
}

void GUI::drawMenuBar(){
	if (!ImGui::BeginMainMenuBar()) return;

	if (!ImGui::BeginMenu("Save")){
		ImGui::EndMainMenuBar();
		return;
	}

	if (ImGui::MenuItem("All Vehicles")) exportAll();

	if (!ImGui::BeginMenu("Specific Vehicle")){
		ImGui::EndMenu();
		ImGui::EndMainMenuBar();
		return;
	}

	if (ImGui::MenuItem("Purple Pickup Truck")) exportVehicle(pickups[0], "Purple Pickup Truck", "purple_pickup.txt");
	if (ImGui::MenuItem("Green Pickup Truck"))  exportVehicle(pickups[1], "Green Pickup Truck", "green_pickup.txt");
	if (ImGui::MenuItem("Black Pickup Truck"))  exportVehicle(pickups[2], "Black Pickup Truck", "black_pickup.txt");

	if (ImGui::MenuItem("Red Compact Car"))	    exportVehicle(compacts[0], "Red Compact Car", "red_compact.txt");
	if (ImGui::MenuItem("Blue Compact Car"))    exportVehicle(compacts[1], "Blue Compact Car", "blue_compact.txt");
	if (ImGui::MenuItem("Yellow Compact Car"))  exportVehicle(compacts[2], "Yellow Compact Car", "yellow_compact.txt");

	if (ImGui::MenuItem("Blue Sedan"))          exportVehicle(sedans[0], "Blue Sedan", "blue_sedan.txt");
	if (ImGui::MenuItem("Black Sedan"))         exportVehicle(sedans[1], "Black Sedan", "black_sedan.txt");
	if (ImGui::MenuItem("Green Sedan"))         exportVehicle(sedans[2], "Green Sedan", "green_sedan.txt");

	ImGui::EndMenu();
	ImGui::EndMenu();
	ImGui::EndMainMenuBar();
}
