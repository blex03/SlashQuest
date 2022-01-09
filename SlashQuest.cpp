#include <iostream>
#include "Rooms.h"

rooms* room = new rooms();
commands* command = new commands();

int main(){
	//Introduction
	std::cout << "SLASH QUEST - BRYAN LECZA" << std::endl;
	std::cout << "January 9, 2022 \n\n";
	
	std::string name;
	std::cout << "Enter your character's name: ";
	std::getline(std::cin, name);
	name = parse->upperCase(name);
	
	std::cout << "\nHello " << name << ", Welcome to Slash Quest.\nIt is your quest to slay the evil dragon! " << std::endl;
	
	command->instructions();
	
	std::cout << "You stand before a cave to your north. Your adventure starts here" << std::endl;
	room->beginning();
	std::cout << "You entered the cave. You see a chest in the northwest corner" << std::endl;

	while (room->running) {
		if (room->room_status == 0) {
			room->cave();
		}

		else if (room->room_status == 1) {
			if (item->end) {
				break;
			}
			room->crossroads();
		}

		else if (room->room_status == 2) {
			room->dragonsRoom();
		}

		else if (room->room_status == 3) {
			room->arrowDungeon();
		}

		else if (room->room_status == 4) {
			room->shop();
		}
	}
	
	std::cin.get();
	
	return 0;
}