#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "imgui.h"
#include <GUI/GUI.hpp>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <thread>
#include <vector>

constexpr char memberSelectInfoFmt[] = "Name: {}\nCredits: {}###{}";

const int ROOT_WINDOW_FLAGS = (
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoResize |
 	ImGuiWindowFlags_NoCollapse |
  	ImGuiWindowFlags_NoDecoration
);

const ImVec2 MEMBER_PANEL_DIMENSIOSN = {
	0.25f,
	0.985f
};

void GUI::drawMembers(){
	float panelW, panelH;

	panelW = ImGui::GetWindowWidth()  * MEMBER_PANEL_DIMENSIOSN.x;
	panelH = ImGui::GetWindowHeight() * MEMBER_PANEL_DIMENSIOSN.y;

	switch (members.size()){
	case 0:
		ImGui::Text("No members\nloaded...");
		return;
	default:
		break;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, {20, 10});
	if (!ImGui::BeginTable(
		"###memberPanel",
		1,
		ImGuiTableFlags_BordersOuter | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_ScrollY,
		{panelW, panelH}
	)){
		ImGui::PopStyleVar();
		ImGui::End();
		return;
	}

	bool selected, match;
	for (Member& member : members){
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);

		match = selectedMember == &member;
		selected = ImGui::Selectable(
			std::format(
				memberSelectInfoFmt,
				member.getName(),
				member.getCredits(),
				(size_t)&member
			).c_str(),
			match,
			ImGuiSelectableFlags_None
		);

		switch (selected) {
			case false: continue;
			default:    break;
		}

		size_t calcAddr = (size_t)&member * (match);

		switch (calcAddr){
			case 0:
				selectedMember = &member;
				break;
			default:
				selectedMember = nullptr;
				break;
		}
	}

	ImGui::PopStyleVar();

	ImGui::EndTable();
}

GUI::GUI(std::string title, uint16_t width, uint16_t height){
	const char* glsl_version = "#version 150";

	if (!glfwInit()) return;

	// Setup OpenGL with GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    switch (width | height) {
    case 0:
    	this->wmHandle = glfwCreateWindow(1280, 720, title.c_str(), 0, 0);
     	glfwMaximizeWindow(this->wmHandle);
      	break;
    default:
    	this->wmHandle = glfwCreateWindow(width, height, title.c_str(), 0, 0);
     	break;
    }

    if (this->wmHandle == nullptr) return;

    glfwMakeContextCurrent(this->wmHandle);
    glfwSwapInterval(1);


    imCtx = ImGui::CreateContext();
	ImGui::SetCurrentContext(imCtx);

    this->ioHandle = &ImGui::GetIO();
    this->vpInfo   =  ImGui::GetMainViewport();

    ImGui::StyleColorsDark();

    ioHandle->Fonts->AddFontFromMemoryTTF(
   		(void*)ROBOTO_MONO_DATA,
     	sizeof(ROBOTO_MONO_DATA),
      	32
    );

    ImGui_ImplGlfw_InitForOpenGL(this->wmHandle, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

bool GUI::run(){
	if (wmHandle == nullptr) return false;

	while (!glfwWindowShouldClose(wmHandle)){
		glfwPollEvents();

        ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize(ioHandle->DisplaySize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::Begin("##root", nullptr, ROOT_WINDOW_FLAGS);
        ImGui::PopStyleVar();

        drawMembers();
        drawVehicles();
        drawCurrentPopup();

        ImGui::ShowDemoWindow();

        ImGui::End();

        ImGui::Render();
        glfwGetFramebufferSize(wmHandle, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(wmHandle);
	}

	// Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    return true;
}

void GUI::setMembersList(std::vector<Member>& members){
	this->members = members;
}
