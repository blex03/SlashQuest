#include <iostream>
#include <string>
#include <algorithm>

#include "Rooms.h"

rooms* room = new rooms();
commands* command = new commands();

int main(){

	//Introduction
	std::cout << "SLASH QUEST - BRYAN LECZA" << std::endl;
	std::cout << "DECEMBER 19, 2021 \n\n";
	
	std::string name;
	std::cout << "Enter your character's name: ";
	std::getline(std::cin, name);
	name = command->upperCase(name);
	
	
	std::cout << "Hello " << name << ", Welcome to Slash Quest" << std::endl;
	
	command->instructions();
	
	std::cout << "You stand before a cave to your north. Your adventure starts here" << std::endl;
	
	while (room->running) {
		if (room->room_status[0] == 1) {
			room->cave();
		}

		else if (room->room_status[1] == 1) {
			room->outside();
		}
	}

	std::cout << "\n\nIt worked!!!:)\n";
	
	std::cin.get();
	
	return 0;
	
}