#include <iostream>
#include <string>
#include <algorithm>
#include "Rooms.h"


rooms* room = new rooms();
commands* command = new commands();

int main(){
	//Introduction
	std::cout << "SLASH QUEST - BRYAN LECZA" << std::endl;
	std::cout << "January 3, 2022 \n\n";
	
	std::string name;
	std::cout << "Enter your character's name: ";
	std::getline(std::cin, name);
	name = parse->upperCase(name);
	
	
	std::cout << "Hello " << name << ", Welcome to Slash Quest" << std::endl;
	
	command->instructions();
	
	std::cout << "You stand before a cave to your north. Your adventure starts here" << std::endl;
	room->beginning();
	std::cout << "You entered the cave. You see a chest in the northwest corner" << std::endl;

	while (room->running) {
		if (room->room_status[0] == 1) {
			room->cave();
		}

		else if (room->room_status[1] == 1) {
			room->crossroads();
		}

		else if (room->room_status[2] == 1) {
			room->theEnd();
			break;
		}
	}

	std::cout << "\nIt worked!!!:)\n";
	
	std::cin.get();
	
	return 0;
	
}