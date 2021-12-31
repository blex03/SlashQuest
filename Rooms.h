#pragma once 
#include <iostream>
#include <vector>
#include "commands.h"

class rooms {

private:
	commands* command = new commands();
	
	enum types : int {
		NONE = 0, CHEST, WALL
	};
	struct loot { //just an ID for now, maybe add a new variable for what might be in the chest, or maybe how strong a wall is or something?
		types id;
	};

	inline void setup_map(int roomSizeX, int roomSizeY) { //This creates the completely empty map, and scales off the roomsize variable

		for (unsigned int y = 0; y < roomSizeY; y++) {
			empty_column.push_back({ NONE });
		}
		for (unsigned int x = 0; x < roomSizeX; x++) {
			map.push_back(empty_column);
		}
		//For display
		map[0][2] = { CHEST };
		map[2][1] = { WALL };
	}

	inline void display(commands::pos coords, int roomSizeX, int roomSizeY, int exit_X) {
		setup_map(roomSizeX, roomSizeY);
		
		std::cout << "-";
		for (unsigned int x = 0; x < roomSizeX; x++) {
			std::cout << "---";
		}
		std::cout << "-";

		std::cout << std::endl;
		for (unsigned int y = roomSizeY; y > 0; y--) {
			std::cout << "|";
			for (unsigned int x = 0; x < roomSizeX; x++) {
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
		for (unsigned int x = exit_X; x < roomSizeX - 1; x++) {
			std::cout << "---";
		}
		std::cout << "-";

		std::cout << "" << std::endl;
	}
	
public:
	//So I can continue the while loop in the main function
	bool running = true;

	//This is so I can determine which room to call in the main function
	int room_status[2] = { 1, 0 };

	

	//insert items like chests, other types of objects that might spawn in the map
	std::vector<std::vector<loot>> map;
	std::vector<loot> empty_column;

	
	
	inline void cave() {

		//Size of room
		int caveSizeX = 3;
		int caveSizeY = 3;
		int exit_X = 1;

		commands::pos coords = { 1, -1 };
		commands::pos chest = { 0, 2 };
		commands::pos exit = { 1, -1 };
		commands::pos walls[1] = { 2, 1 };
								  
		
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

			//Phrases only display if player has moved
			if (!(coords == previous_coords)) {

				//Chest
				if (coords == commands::pos(chest)) {
					std::cout << "You see a chest in front of you" << std::endl;
					item->chest_proximity = true;
				}
				else {
					item->chest_proximity = false;
				}

				//Entry
				if (coords.y == 0 && previous_coords.y < 0) {
					std::cout << "You entered the cave. You see a chest in the northwest corner" << std::endl;
				}

				//Checks if player reached a boundary
				if (coords.x == caveSizeX || coords.y == caveSizeY || coords.x < 0 || coords.y < 0) {
					if (coords.y < 0 && previous_coords.y < 0) {
						std::cout << "You try to move that way, but something draws you into the cave" << std::endl;
						coords = previous_coords;
					}

					//Exit
					else if (coords.x == exit.x && coords.y < 0 && previous_coords.y >= 0) {
						std::cout << "You left the cave" << std::endl;
					}

					else {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}

				for (int i = 0; i < 1; i++) {
					if (coords == commands::pos(walls[i])) {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}
			}
			
			if (coords.y >= 0) {
				std::cout << std::endl;
				std::cout << "CAVE" << std::endl;
				display(coords, caveSizeX, caveSizeY, exit_X);
			}

			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";
		}

		room_status[0] = 0;
		room_status[1] = 1;
	}

	inline void outside() {

		std::cout << "You made it outside!";
		running = false;
	}
};