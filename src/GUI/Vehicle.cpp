#include "imgui.h"
#include <GUI/GUI.hpp>
#include <cstddef>
#include <cstring>
#include <format>
#include <iostream>

void GUI::drawVehicles(){
	ImGui::SameLine();

	bool tableMade = ImGui::BeginTable(
		"##vehicleList",
		3,
		ImGuiTableFlags_BordersOuter | ImGuiTableFlags_SizingStretchSame
	);

	if (!tableMade) return;

	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	for (Pickup&  pickup  : pickups) drawPickup(pickup);
	// ImGui::TableNextRow();
	for (Compact& compact : compacts) drawCompact(compact);
	// ImGui::TableNextRow();
	for (Sedan&   sedan   : sedans) drawSedan(sedan);

	ImGui::EndTable();
}

void GUI::drawPickup(Pickup& pickup){
	ReservationResult status;
	auto& reservations = pickup.getReservations();

	bool tableMade = ImGui::BeginTable(
		std::format("##{}", (size_t)&pickup).c_str(),
		1,
		ImGuiTableFlags_BordersOuter | ImGuiTableFlags_SizingStretchSame
	);

	if (!tableMade) return;

	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);

	if (
		selectedMember == NULL &&
		pickup.getReservations().at(0).isTaken()
	){
		if (ImGui::Button(
			std::format("Drop##{}", (size_t)&pickup).c_str(),
			{100, 100}
		)){
			popupState             = INPUT;
			popupReservationToDrop = &reservations.at(0);
		}
	} else if (
		selectedMember != NULL &&
		!pickup.getReservations().at(0).isTaken()
	) {
		if (ImGui::Button(
			std::format("Take##{}", (size_t)&pickup).c_str(),
			{100, 100}
		)){
			status = reservations.at(0).take(*selectedMember);
			switch (status) {
			case ReservationResult::TOO_FEW_CREDITS:
				popupMessage = "Too few credits...";
				popupState   = MESSAGE;
				break;
			default:
				popupMessage = std::format(
					"Reservation pin is: {}",
					reservations.at(0).getPin().data()
				);
				popupState     = MESSAGE;
				selectedMember = nullptr;
				break;
			}
		}
	} else {
		ImGui::BeginDisabled();
		ImGui::Button(
			std::format("##placeholder{}", (size_t)&pickup).c_str(),
			{100, 100}
		);
		ImGui::EndDisabled();
	}

	ImGui::TableNextRow(ImGuiTableRowFlags_None, 100);
	ImGui::TableNextRow(ImGuiTableRowFlags_None, 100);
	ImGui::TableSetColumnIndex(0);

	drawDriver(pickup.getDriver());

	ImGui::EndTable();

	ImGui::TableNextColumn();
}

void GUI::drawCompact(Compact& compact){
}

void GUI::drawSedan(Sedan& sedan){
}

void GUI::drawDriver(const std::string& name){
	ImGui::BeginDisabled();
	ImGui::Button(
		std::format("##{}", name).c_str(),
		{100, 100}
	);
	ImGui::SetItemTooltip(
		"Driver: %s", name.c_str()
	);
	ImGui::EndDisabled();
}

void GUI::drawCurrentPopup(){
	if (popupState == NONE) return;

	if (!ImGui::IsPopupOpen("###message")) ImGui::OpenPopup("###message");
	if (!ImGui::BeginPopupModal(
		"###message",
		NULL,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_Modal | ImGuiWindowFlags_Popup | ImGuiWindowFlags_AlwaysAutoResize
	)) return;

	switch (popupState) {
	case MESSAGE:
		if (!popupMessage.has_value()) return;
		ImGui::Text("%s", popupMessage.value().c_str());
		if (ImGui::Button("Ok##popupClose")){
			popupState = NONE;
			popupMessage.reset();
			ImGui::CloseCurrentPopup();
		}
		break;
	case INPUT:
		ImGui::InputTextWithHint("##pinInput", "Enter reservation pin...", popupInput.data(), 9, ImGuiInputTextFlags_CharsDecimal);
		if (ImGui::Button("Ok##popupClose")){
			popupState = NONE;
			popupMessage.reset();
			ImGui::CloseCurrentPopup();

			ReservationResult status = popupReservationToDrop->drop(popupInput);

			if (status != ReservationResult::SUCCESS){
				popupReservationToDrop = nullptr;
				popupMessage = "Invalid pin given, leaving reservation.";
				popupState   = MESSAGE;
			}

			memset(popupInput.data(), 0, 8);
		}
		break;
	default:
		break;
	}

	ImGui::EndPopup();
}
