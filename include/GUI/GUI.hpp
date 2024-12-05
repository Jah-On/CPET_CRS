// STD Includes
#include <array>
#include <cstdint>
#include <optional>
#include <vector>

// GUI Includes
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

// App Includes
#include <Vehicle.hpp>

// Font Include
#include "RobotoMono.h"

class GUI {
public:
	/*
		GUI class constructor.

		Parameters:
			std::string title: Sets the window title.
			uint16_t width: Sets the window width; default is 0 for maximized window.
			uint16_t height: Sets the window height; default is 0 for maximized window.
		Returns:
			Class instance.
	*/
	GUI(std::string title, uint16_t width = 0, uint16_t height = 0);

	/*
		Provides the GUI with a list of club members.

		Parameters:
			std::vector<Member>& members: Reference vector
				containing the club members.
		Returns:
	*/
	void setMembersList(std::vector<Member>& members);

	/*
		Starts the GUI.

		Parameters:
		Returns: bool indicating whether the GUI ran successfully.
	*/
	bool run();
private:
	// Rendering Functions
	void drawMenuBar();

	void drawMembers();
	void drawVehicles();
	void drawPickup(Pickup& pickup);
	void drawCompact(Compact& compact);
	void drawSedan(Sedan& sedan);

	void drawDriver(const std::string& name);
	void drawReservation(Reservation& seat);

	void drawCurrentPopup();

	// Export Functions
	template <class T>
	void exportVehicle(
		T& vehicle,
		std::string title,
		std::string file,
		std::ofstream* open = NULL
	);
	void exportAll();
	void exportMembers();

	// WM and Widget Library Variables
	int                		width, height;
	ImGuiContext*           imCtx          = nullptr;
	ImGuiIO*           		ioHandle       = nullptr;
	ImGuiViewport*     		vpInfo         = nullptr;
	GLFWwindow*        		wmHandle       = nullptr;

	// Popup Related Variables
	enum {
		NONE,
		MESSAGE,
		INPUT,
		EXPORT_ALL
	} popupState = NONE;
	std::optional<std::string> popupMessage          = std::nullopt;
	Pin                        popupInput            = {0};
	Reservation*               popupReservationToDrop;
	std::string                popupExportAllPassword;

	// Vehicles
	std::array<Pickup,  3>  pickups = {
		Pickup("Pat Cooper",    VehicleColor::PURPLE),
		Pickup("Jane Cox",      VehicleColor::GREEN),
		Pickup("Tim Taylor",    VehicleColor::BLACK)
	};
	std::array<Compact, 3>  compacts = {
		Compact("Ben Butler",   VehicleColor::RED),
		Compact("Art Campbell", VehicleColor::BLUE),
		Compact("Ann Edwards",  VehicleColor::YELLOW)
	};
	std::array<Sedan,   3>  sedans = {
		Sedan("Grace Wan",      VehicleColor::BLUE),
		Sedan("Larry Adams",    VehicleColor::BLACK),
		Sedan("Jess Quirk",     VehicleColor::GREEN)
	};

	// Member Info Variables
	std::vector<Member>		members;
	Member* 				selectedMember = nullptr;
};
