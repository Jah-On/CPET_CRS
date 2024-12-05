#include <GUI/GUI.hpp>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

const std::string MEMBER_FILE = "./assets/dodgeball_team.txt";

std::vector<Member> loadMembers(){
	std::vector<Member> memberList = {};

	std::ifstream file_(MEMBER_FILE);

	if (!file_.is_open()) throw "Could not open file!";

	std::string line;
	size_t      lastSpace;

	for (uint8_t i = 0; i < 9; ++i) std::getline(file_, line);

	while (!file_.eof()) {
		std::getline(file_, line);

		if (!line.length()) break;

		lastSpace = line.rfind(' ');

		memberList.emplace_back(
			line.substr(0, lastSpace),
			std::stoi(line.substr(lastSpace + 1))
		);
	}

	return memberList;
}

int main(){
	std::vector<Member> memberList = loadMembers();

	GUI ui = GUI("CPET CRS");

	ui.setMembersList(memberList);

	ui.run();

	return 0;
}
