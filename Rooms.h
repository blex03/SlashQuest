#pragma once 
#include <iostream>
#include "commands.h"

#include <vector>

class rooms {

private:
	commands* command = new commands();
	
	enum types : int {
		NONE = 0, CHEST, WALL
	};
	struct loot { //just an ID for now, maybe add a new variable for what might be in the chest, or maybe how strong a wall is or something?
		types id;
	};


public:
	//So I can continue the while loop in the main function
	bool running = true;

	//This is so I can determine which room to call in the main function
	int room_status[2] = { 1, 0 };

	//Size of room
	int roomSize = 5;
	int exit_X = 1;

	//insert items like chests, other types of objects that might spawn in the map
	std::vector<std::vector<loot>> map;
	std::vector<loot> empty_row;

	inline void setup_map() { //This creates the completely empty map, and scales off the roomsize variable
		for (unsigned int x = 0; x < roomSize; x++) {
			empty_row.push_back({NONE});
		}
		for (unsigned int y = 0; y < roomSize; y++) {
			map.push_back(empty_row);
		}
		map[0][3] = { CHEST };
	}
	inline void display(commands::pos coords) {
		std::cout << "(" << coords.x << "," << coords.y << ")";
		std::cout << "Coins: " << item->gold_amount << std::endl;
		
		std::cout << "-";
		for (unsigned int x = 0; x < roomSize; x++) {
			std::cout << "---";
		}
		std::cout << "-";

		std::cout << std::endl;
		for (unsigned int y = roomSize; y > 0; y--) {
			std::cout << "|";
			for (unsigned int x = 0; x < roomSize; x++) {
				std::cout << "[";
				if (coords == commands::pos::to_pos(x, y - 1)) {
					std::cout << "P";
					if (map[x][y - 1].id != NONE) {
						std::cout << "*";
					}
				}
				else if (map[x][y - 1].id == CHEST) {
					std::cout << "C";
				}
				else if (map[x][y - 1].id == WALL) {
					std::cout << "X";
				}
				else { 
					std::cout << " ";
				}

				std::cout << "]";
			}
			std::cout << "|" << std::endl;
		}

		std::cout << "-";
		for (unsigned int x = 0; x < exit_X; x++) {
			std::cout << "---";
		}
		std::cout << "| |";
		for (unsigned int x = exit_X; x < roomSize - 1; x++) {
			std::cout << "---";
		}
		std::cout << "-";
		
		std::cout << "" << std::endl;
	}

	inline void cave() {

		commands::pos coords = { 1, -1 };
		commands::pos chest = { 0, 3 };
		commands::pos exit = { 1, -1 };
		
		while (true) {

			//So player will backtrack when they hit a boundary
			//Can also compare previous_coords to coords to track direction player is moving
			commands::pos previous_coords = coords;
			coords = command->userSpace(coords.x, coords.y);

			//End while loop with this condition-----------------------------------
			if (coords == commands::pos::to_pos(1, -1) && item->cave_chest == true) {
				break;
			}
			//---------------------------------------------------------------------

			//Checks if player reached a boundary
			if (coords.x == roomSize || coords.y == roomSize || coords.x < 0 || coords.y < 0) {
				if ((coords.x == exit.x && coords.y < 0) || (coords.x != exit.x && coords.y < 0 && previous_coords.y < 0)) {
					std::cout << "You try to move that way, but something draws you into the cave" << std::endl;
					coords = previous_coords;
				}

				else{
					std::cout << "You hit a wall" << std::endl;
					coords = previous_coords;
				}
			}
			display(coords);

			//chest
			if (coords == commands::pos(chest)) {
				std::cout << "You see a chest in front of you" << std::endl;
				item->chest_proximity = true;
			}
			else {
				item->chest_proximity = false;
			}
		}

		room_status[0] = 0;
		room_status[1] = 1;

	}

	inline void outside() {

		std::cout << "You made it outside!";
		running = false;
	}

};