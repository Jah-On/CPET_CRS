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
	GUI(std::string title, uint16_t width = 0, uint16_t height = 0);

	void setMembersList(std::vector<Member>& members);

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

	int                		width, height;
	ImGuiContext*           imCtx          = nullptr;
	ImGuiIO*           		ioHandle       = nullptr;
	ImGuiViewport*     		vpInfo         = nullptr;
	GLFWwindow*        		wmHandle       = nullptr;

	enum {
		NONE,
		MESSAGE,
		INPUT
	} popupState = NONE;

	std::optional<std::string> popupMessage = std::nullopt;
	Pin                        popupInput   = {0};
	Reservation*               popupReservationToDrop;

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

	std::vector<Member>		members;
	Member* 				selectedMember = nullptr;
};
