#pragma once 
#include <iostream>
#include <vector>
#include "commands.h"

class rooms {

private:
	commands* command = new commands();
	
	enum areas : int {
		CAVE,
		CROSSROADS,
		EASTROOM,
		WESTROOM,
		SOUTHROOM
	};

	enum types : int {
		NONE = 0, 
		CHEST,
		WALL, 
		DOOR
	};
	struct loot { //just an ID for now, maybe add a new variable for what might be in the chest, or maybe how strong a wall is or something?
		types id;
	};
	//insert items like chests, other types of objects that might spawn in the map
	std::vector<std::vector<loot>> map;
	std::vector<loot> empty_column;

	//Bounds
	std::vector<loot> north_bound;
	std::vector<loot> south_bound;
	std::vector<loot> east_bound;
	std::vector<loot> west_bound;

	inline void setup_map(int roomSizeX, int roomSizeY) { //This creates the completely empty map, and scales off the roomsize variable
		empty_column.clear();
		map.clear();
		north_bound.clear();
		south_bound.clear();
		east_bound.clear();
		west_bound.clear();
		
		for (unsigned int y = 0; y < roomSizeY; y++) {
			empty_column.push_back({ NONE });
		}
		for (unsigned int x = 0; x < roomSizeX; x++) {
			map.push_back(empty_column);
		}

		//Bounds
		for (unsigned int y = 0; y < roomSizeY; y++) {
			north_bound.push_back({ NONE });
		}
		for (unsigned int y = 0; y < roomSizeY; y++) {
			south_bound.push_back({ NONE });
		}
		for (unsigned int x = 0; x < roomSizeY; x++) {
			east_bound.push_back({ NONE });
		}
		for (unsigned int x = 0; x < roomSizeY; x++) {
			west_bound.push_back({ NONE });
		}
	
	}

	inline void display(commands::pos coords, int roomSizeX, int roomSizeY) {
		
		std::cout << "   -";
		for (unsigned int x = 0; x < roomSizeX; x++) {
			
			if (north_bound[x].id == NONE) {
				std::cout << "---";
			}

			else {
				std::cout << "| |";
			}
		}
		std::cout << "-";

		std::cout << std::endl;
		for (unsigned int y = roomSizeY; y > 0; y--) {
			if (west_bound[y - 1].id == NONE) {
				std::cout << "   |";
			}
			else {
				std::cout << "  = ";
			}

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
			if (east_bound[y - 1].id == NONE) {
				std::cout << "|";
			}
			else {
				std::cout << " =";
			}

			std::cout << std::endl;
		}

		std::cout << "   -";
		for (unsigned int x = 0; x < roomSizeX; x++) {

			if (south_bound[x].id == NONE) {
				std::cout << "---";
			}

			else {
				std::cout << "| |";
			}
		}
		std::cout << "-";
		
		std::cout << std::endl;
	}
	
public:
	//So I can continue the while loop in the main function
	bool running = true;

	//This is so I can determine which room to call in the main function
	
	areas room_status = CAVE;
	areas previous_room;

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
		south_bound[1] = { DOOR };
								  
		commands::pos coords = { 1, 0 };
		commands::pos chest = { 0, 2 };
		commands::pos exit = { 1, -1 };
		commands::pos walls[1] = { 2, 2 };
		
		while (true) {

			std::cout << "\n   CAVE" << std::endl;
			display(coords, caveSizeX, caveSizeY);
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
		previous_room = CAVE;
		room_status = CROSSROADS;
	}

	inline void crossroads() {
		//Size of room
		int roomSizeX = 3;
		int roomSizeY = 3;

		//For display
		setup_map(roomSizeX, roomSizeY);
		map[0][0] = { WALL };
		map[2][0] = { WALL };
		map[0][2] = { WALL };
		map[2][2] = { WALL };

		north_bound[1] = { DOOR };
		south_bound[1] = { DOOR };
		east_bound[1] = { DOOR };
		west_bound[1] = { DOOR };

		commands::pos coords;

		if (previous_room == CAVE) {
			coords = { 1, 2 };
		}
		else if (previous_room == WESTROOM) {
			coords = { 0, 1 };
		}
		else if (previous_room == EASTROOM) {
			coords = { 2, 1 };
		}
		else {
			coords = { 1, 0 };
		}

		commands::pos exit_N = { 1, 3 };
		commands::pos exit_S = { 1, -1 };
		commands::pos exit_E = { 3, 1 };
		commands::pos exit_W = { -1, 1 };
		commands::pos walls[4] = { 
								   {0, 0},
								   {2, 0},
								   {0, 2},
								   {2, 2} 
								};
		while (true) {
			std::cout << "\n   CROSSROADS" << std::endl;
			display(coords, roomSizeX, roomSizeY);
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";

			//So player will backtrack when they hit a boundary
			//Can also compare previous_coords to coords to track direction player is moving
			commands::pos previous_coords = coords;
			coords = command->userSpace(coords.x, coords.y);

			//End while loop with this condition-----------------------------------
			if (coords == commands::pos(exit_S) || coords == commands::pos(exit_N) || coords == commands::pos(exit_E) || coords == commands::pos(exit_W)) {
				break;
			}
			//---------------------------------------------------------------------

			//Phrases only display if player has moved
			if (!(coords == previous_coords)) {
				
				//Checks if player reached a boundary
				if (coords.x == roomSizeX || coords.y == roomSizeY || coords.x < 0 || coords.y < 0) {
					
					if (!(coords == commands::pos(exit_S) || coords == commands::pos(exit_N) || coords == commands::pos(exit_E))) {
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

		

		if (coords == commands::pos(exit_N)) {
			room_status = CAVE;
		}
		else if (coords == commands::pos(exit_S)) {
			room_status = SOUTHROOM;
		}
		else if (coords == commands::pos(exit_E)) {
			room_status = EASTROOM;
		}
		else {
			room_status = WESTROOM;
		}
		


	}

	inline void eastRoom() {
		//Size of room
		int roomSizeX = 5;
		int roomSizeY = 5;

		//For display
		setup_map(roomSizeX, roomSizeY);
		west_bound[2] = { DOOR };
		
		commands::pos coords = { 0, 2 };
		commands::pos exit = { -1, 2 };

		while (true) {
			std::cout << "\n   EASTROOM" << std::endl;
			display(coords, roomSizeX, roomSizeY);
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

			//Phrases only display if player has moved
			if (!(coords == previous_coords)) {

				//Checks if player reached a boundary
				if (coords.x == roomSizeX || coords.y == roomSizeY || coords.x < 0 || coords.y < 0) {

					if (!(coords == commands::pos(exit))) {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}
			}
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";
		}
		previous_room = EASTROOM;
		room_status = CROSSROADS;
	}

	inline void westRoom() {
		//Size of room
		int roomSizeX = 5;
		int roomSizeY = 5;

		//For display
		setup_map(roomSizeX, roomSizeY);
		east_bound[2] = { DOOR };

		commands::pos coords = { 4, 2 };
		commands::pos exit = { 5, 2 };

		while (true) {
			std::cout << "\n   WESTROOM" << std::endl;
			display(coords, roomSizeX, roomSizeY);
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

			//Phrases only display if player has moved
			if (!(coords == previous_coords)) {

				//Checks if player reached a boundary
				if (coords.x == roomSizeX || coords.y == roomSizeY || coords.x < 0 || coords.y < 0) {

					if (!(coords == commands::pos(exit))) {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}
			}
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";
		}
		previous_room = WESTROOM;
		room_status = CROSSROADS;
	}

	inline void southRoom() {
		//Size of room
		int roomSizeX = 5;
		int roomSizeY = 5;

		//For display
		setup_map(roomSizeX, roomSizeY);
		north_bound[2] = { DOOR };

		commands::pos coords = { 2, 4 };
		commands::pos exit = { 2, 5 };

		while (true) {
			std::cout << "\n   SOUTHROOM" << std::endl;
			display(coords, roomSizeX, roomSizeY);
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

			//Phrases only display if player has moved
			if (!(coords == previous_coords)) {

				//Checks if player reached a boundary
				if (coords.x == roomSizeX || coords.y == roomSizeY || coords.x < 0 || coords.y < 0) {

					if (!(coords == commands::pos(exit))) {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}
			}
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";
		}
		previous_room = SOUTHROOM;
		room_status = CROSSROADS;
	}
};