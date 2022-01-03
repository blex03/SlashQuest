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
		empty_column.clear();
		map.clear();
		
		for (unsigned int y = 0; y < roomSizeY; y++) {
			empty_column.push_back({ NONE });
		}
		for (unsigned int x = 0; x < roomSizeX; x++) {
			map.push_back(empty_column);
		}
	}

	inline void display(commands::pos coords, int roomSizeX, int roomSizeY, int south_exit = NONE, int north_exit = NONE) {
		std::cout << "-";
		if (north_exit != NONE) {
			for (unsigned int x = 0; x < south_exit; x++) {
				std::cout << "---";
			}
			std::cout << "| |";
			for (unsigned int x = south_exit; x < roomSizeX - 1; x++) {
				std::cout << "---";
			}
		}
		else {
			for (unsigned int x = 0; x < roomSizeX; x++) {
				std::cout << "---";
			}
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

		if (south_exit != NONE) {
			std::cout << "-";
			for (unsigned int x = 0; x < south_exit; x++) {
				std::cout << "---";
			}
			std::cout << "| |";
			for (unsigned int x = south_exit; x < roomSizeX - 1; x++) {
				std::cout << "---";
			}
			std::cout << "-";
		}

		else {
			std::cout << "-";
			for (unsigned int x = 0; x < roomSizeX; x++) {
				std::cout << "---";
			}
			std::cout << "-";
		}

		std::cout << std::endl;
	}
	
public:
	//So I can continue the while loop in the main function
	bool running = true;

	//This is so I can determine which room to call in the main function
	int room_status[3] = { 1, 0, 0 };

	//insert items like chests, other types of objects that might spawn in the map
	std::vector<std::vector<loot>> map;
	std::vector<loot> empty_column;
	
	inline void beginning() {
		commands::pos coords = { 1, -1 };
		commands::pos exit = { 1, 0 };

		while (true) {

			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";
			//So player will backtrack when they hit a boundary
			//Can also compare previous_coords to coords to track direction player is moving
			commands::pos previous_coords = coords;
			coords = command->userSpace(coords.x, coords.y);

			//End while loop with this condition-----------------------------------
			if (coords == commands::pos(exit)) {
				break;
			}
			//---------------------------------------------------------------------
			
			//Checks if player reached a boundary
			if (!(coords == commands::pos(exit))) {
				std::cout << "You try to move that way, but something draws you into the cave" << std::endl;
				coords = previous_coords;
			}
		}
	}

	inline void cave() {
		//Size of room
		int caveSizeX = 3;
		int caveSizeY = 3;
		int south_exit = 1;

		//For display
		setup_map(caveSizeX, caveSizeY);
		map[0][2] = { CHEST };
		map[2][2] = { WALL };
								  
		commands::pos coords = { 1, 0 };
		commands::pos chest = { 0, 2 };
		commands::pos exit = { 1, -1 };
		commands::pos walls[1] = { 2, 2 };
		
		while (true) {

			std::cout << "\nCAVE" << std::endl;
			display(coords, caveSizeX, caveSizeY, south_exit);
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";
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

				//Checks if player reached a boundary
				if (coords.x == caveSizeX || coords.y == caveSizeY || coords.x < 0 || coords.y < 0) {
					
					//Exit
					if (coords == commands::pos(exit)) {
						std::cout << "You left the cave" << std::endl;
						beginning();
						coords = { 1, 0 };
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
			
			
			
		}

		room_status[0] = 0;
		room_status[1] = 1;
	}

	inline void crossroads() {
		//Size of room
		int roomSizeX = 3;
		int roomSizeY = 3;
		int north_exit = 1;
		int south_exit = 1;

		//For display
		setup_map(roomSizeX, roomSizeY);
		map[0][0] = { WALL };
		map[2][0] = { WALL };
		map[0][2] = { WALL };
		map[2][2] = { WALL };

		commands::pos coords = { 1, 2 };
		commands::pos exit_S = { 1, -1 };
		commands::pos exit_N = { 1, 3 };
		commands::pos walls[4] = { 
								   {0, 0},
								   {2, 0},
								   {0, 2},
								   {2, 2} 
								};
		while (true) {
			std::cout << "CROSSROADS" << std::endl;
			display(coords, roomSizeX, roomSizeY, south_exit, north_exit);
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";

			//So player will backtrack when they hit a boundary
			//Can also compare previous_coords to coords to track direction player is moving
			commands::pos previous_coords = coords;
			coords = command->userSpace(coords.x, coords.y);

			//End while loop with this condition-----------------------------------
			if (coords == commands::pos(exit_S) || coords == commands::pos(exit_N)) {
				break;
			}
			//---------------------------------------------------------------------

			//Phrases only display if player has moved
			if (!(coords == previous_coords)) {
				
				//Checks if player reached a boundary
				if (coords.x == roomSizeX || coords.y == roomSizeY || coords.x < 0 || coords.y < 0) {
					
					if (!(coords == commands::pos(exit_S) || coords == commands::pos(exit_N))) {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}

				for (int i = 0; i < 4; i++) {
					if (coords == commands::pos(walls[i])) {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}
			}
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";
		}

		room_status[1] = 0;
		if (coords == commands::pos(exit_S)) {
			room_status[2] = 1;
		}
		if (coords == commands::pos(exit_N)) {
			room_status[0] = 1;
		}


	}

	inline void theEnd() {
		std::cout << "You win!" << std::endl;
	}
};