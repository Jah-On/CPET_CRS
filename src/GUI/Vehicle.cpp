#include "imgui.h"
#include <GUI/GUI.hpp>
#include <array>
#include <cstddef>
#include <cstring>
#include <format>
#include <map>

static const std::map<VehicleColor, ImU32> COLOR_MAP = {
	{VehicleColor::BLACK,  ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f))},
	{VehicleColor::BLUE,   ImGui::ColorConvertFloat4ToU32(ImVec4(0.2f, 0.2f, 1.0f, 1.0f))},
	{VehicleColor::GREEN,  ImGui::ColorConvertFloat4ToU32(ImVec4(0.2f, 0.9f, 0.2f, 1.0f))},
	{VehicleColor::PURPLE, ImGui::ColorConvertFloat4ToU32(ImVec4(0.8f, 0.0f, 0.8f, 1.0f))},
	{VehicleColor::RED,    ImGui::ColorConvertFloat4ToU32(ImVec4(0.9f, 0.1f, 0.1f, 1.0f))},
	{VehicleColor::YELLOW, ImGui::ColorConvertFloat4ToU32(ImVec4(0.8f, 0.9f, 0.0f, 1.0f))}
};

void GUI::drawVehicles(){
	ImGui::SameLine();

	bool tableMade = ImGui::BeginTable(
		"##vehicleList",
		3,
		ImGuiTableFlags_BordersOuter | ImGuiTableFlags_SizingStretchSame
	);

	if (!tableMade) return;

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2);
	ImGui::PushStyleColor(ImGuiCol_Button,           ImVec4(0.10f, 0.10f, 0.10f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered,    ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Button,           ImVec4(0.20f, 0.20f, 0.20f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TextDisabled,     ImVec4(0.10f, 0.10f, 0.10f, 0.8f));

	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	for (Pickup&  pickup  : pickups) drawPickup(pickup);
	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	for (Compact& compact : compacts) drawCompact(compact);
	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	for (Sedan&   sedan   : sedans) drawSedan(sedan);

	ImGui::PopStyleColor(4);
	ImGui::PopStyleVar();

	ImGui::EndTable();
}

void GUI::drawPickup(Pickup& pickup){
	std::array<Reservation, 1>& reservations = pickup.getReservations();

	ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, COLOR_MAP.at(pickup.getColor()));

	bool tableMade = ImGui::BeginTable(
		std::format("##{}", (size_t)&pickup).c_str(),
		1,
		ImGuiTableFlags_BordersOuter | ImGuiTableFlags_SizingStretchSame
	);

	if (!tableMade) return;

	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);

	drawReservation(reservations[0]);

	ImGui::TableNextRow(ImGuiTableRowFlags_None, 100);
	ImGui::TableNextRow(ImGuiTableRowFlags_None, 100);
	ImGui::TableSetColumnIndex(0);

	drawDriver(pickup.getDriver());

	ImGui::EndTable();

	ImGui::TableNextColumn();
}

void GUI::drawCompact(Compact& compact){
	std::array<Reservation, 3>& reservations = compact.getReservations();

	ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, COLOR_MAP.at(compact.getColor()));

	bool tableMade = ImGui::BeginTable(
		std::format("##{}", (size_t)&compact).c_str(),
		2,
		ImGuiTableFlags_BordersOuter | ImGuiTableFlags_SizingStretchSame
	);

	if (!tableMade) return;

	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);

	drawReservation(reservations[0]);

	ImGui::TableNextColumn();

	drawReservation(reservations[1]);

	ImGui::TableNextRow(ImGuiTableRowFlags_None, 100);
	ImGui::TableNextRow(ImGuiTableRowFlags_None, 100);
	ImGui::TableSetColumnIndex(0);

	drawDriver(compact.getDriver());

	ImGui::TableNextColumn();

	drawReservation(reservations[2]);

	ImGui::EndTable();

	ImGui::TableNextColumn();
}

void GUI::drawSedan(Sedan& sedan){
	std::array<Reservation, 4>& reservations = sedan.getReservations();

	ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, COLOR_MAP.at(sedan.getColor()));

	bool tableMade = ImGui::BeginTable(
		std::format("##{}", (size_t)&sedan).c_str(),
		2,
		ImGuiTableFlags_BordersOuter | ImGuiTableFlags_SizingStretchSame
	);

	if (!tableMade) return;

	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);

	drawReservation(reservations[0]);

	ImGui::TableNextColumn();

	drawReservation(reservations[1]);

	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(1);

	drawReservation(reservations[2]);

	ImGui::TableNextRow(ImGuiTableRowFlags_None, 100);
	ImGui::TableSetColumnIndex(0);

	drawDriver(sedan.getDriver());

	ImGui::TableNextColumn();

	drawReservation(reservations[3]);

	ImGui::EndTable();

	ImGui::TableNextColumn();
}

void GUI::drawDriver(const std::string& name){
	ImGui::BeginDisabled();
	ImGui::Button(
		std::format("Driver##{}", name).c_str(),
		{100, 100}
	);
	ImGui::SetItemTooltip(
		"Driver: %s", name.c_str()
	);
	ImGui::EndDisabled();
}

void GUI::drawReservation(Reservation& seat){
	bool buttonState;
	bool memberSelected = selectedMember != NULL;

	if (seat.isTaken()){
		buttonState = ImGui::Button(
			std::format("Drop##{}", (size_t)&seat).c_str(),
			{100, 100}
		);

		ImGui::SetItemTooltip(
			"Seat taken by %s,\nclick to remove...",
			seat.assinedTo().c_str()
		);

		if (!buttonState) return;

		popupState             = INPUT;
		popupReservationToDrop = &seat;

		return;
	}

	if (
		(!memberSelected && !seat.isTaken()) ||
		(memberSelected  && (selectedMember->getCredits() - seat.getCost() < 0))
	){
		ImGui::BeginDisabled();
		ImGui::Button(
			std::format("{}##placeholder{}", seat.getCost(), (size_t)&seat).c_str(),
			{100, 100}
		);
		ImGui::EndDisabled();

		if (memberSelected){
			ImGui::SetItemTooltip("Too expensive...");
			return;
		}

		ImGui::SetItemTooltip("Select member to\nshow availability...");

		return;
	}

	buttonState = ImGui::Button(
		std::format("Take##{}", (size_t)&seat).c_str(),
		{100, 100}
	);

	switch (seat.getCost()){
	case 1:
		ImGui::SetItemTooltip("Back middle seat\ncosts one point...");
		break;
	case 2:
		ImGui::SetItemTooltip("Tighter back door seat\ncosts two points...");
		break;
	case 3:
		ImGui::SetItemTooltip("Spacious back door seat\ncosts three points...");
		break;
	default:
		ImGui::SetItemTooltip("Front passenger seat\ncosts five points...");
		break;
	}

	if (!buttonState) return;

	ReservationResult status = seat.take(*selectedMember);

	switch (status) {
	case ReservationResult::TOO_FEW_CREDITS:
		popupMessage = "Too few credits...";
		popupState   = MESSAGE;
		break;
	default:
		popupMessage = std::format(
			"Reservation pin is: {}",
			seat.getPin().data()
		);
		popupState     = MESSAGE;
		selectedMember = nullptr;
		break;
	}
}
