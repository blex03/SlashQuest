#pragma once 
#include <iostream>
#include "commands.h"

class rooms {
private:
	commands* command = new commands();
	
	enum areas : int {
		CAVE,
		CROSSROADS,
		DRAGONSROOM,
		ARROWDUNGEON,
		SHOP
	};

	enum types : int {
		NONE = 0, 
		CHEST,
		WALL, 
		DOOR,
		STORE,
		ARROW,
		SHIELD,
		DRAGON,
		FIRE
		
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
		for (unsigned int x = 0; x < roomSizeX; x++) {
			north_bound.push_back({ NONE });
		}
		for (unsigned int x = 0; x < roomSizeX; x++) {
			south_bound.push_back({ NONE });
		}
		for (unsigned int y = 0; y < roomSizeY; y++) {
			east_bound.push_back({ NONE });
		}
		for (unsigned int y = 0; y < roomSizeY; y++) {
			west_bound.push_back({ NONE });
		}
	
	}

	inline bool display(commands::pos coords, commands::pos previous_coords, int roomSizeX, int roomSizeY) {
		
		bool death = false;

		std::cout << "   -";
		for (unsigned int x = 0; x < roomSizeX; x++) {
			
			if (north_bound[x].id == DOOR) {
				std::cout << "| |";
			}

			else {
				std::cout << "---";
			}
		}
		std::cout << "-";

		std::cout << std::endl;
		for (unsigned int y = roomSizeY; y > 0; y--) {
			if (west_bound[y - 1].id == DOOR) {
				std::cout << "  = ";
			}
			else {
				std::cout << "   |";
			}

			for (unsigned int x = 0; x < roomSizeX; x++) {
				std::cout << "[";
				if (coords == commands::pos::to_pos(x, y - 1) && map[coords.x][coords.y].id != SHIELD) {
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
				else if (map[x][y - 1].id == STORE) {
					std::cout << "S";
				}
				else if (map[x][y - 1].id == ARROW && map[x][y - 1].id != SHIELD) {
					std::cout << "->";
				}
				else if (map[x][y - 1].id == SHIELD) {
					std::cout << "#";
				}
				else if (map[x][y - 1].id == FIRE && map[x][y - 1].id != SHIELD) {
					std::cout << "0";
				}
				
				else {
					std::cout << " ";
				}

				std::cout << "]";
			}
			if (east_bound[y - 1].id == DOOR) {
				std::cout << " =";
			}
			else if (east_bound[y - 1].id == DRAGON) {
				std::cout << " ]--===============";
			}
			else {
				std::cout << "|";
			}

			std::cout << std::endl;
		}

		std::cout << "   -";
		for (unsigned int x = 0; x < roomSizeX; x++) {

			if (south_bound[x].id == DOOR) {
				std::cout << "| |";
			}

			else {
				std::cout << "---";
			}
		}
		std::cout << "-";
		
		std::cout << std::endl;

		if (map[coords.x][coords.y].id != SHIELD) {
			if (coords.x < roomSizeX - 1) {
				if (map[coords.x + 1][coords.y].id == ARROW && map[previous_coords.x][previous_coords.y].id == ARROW) {
					death = true;
				}
			}

			if (map[coords.x][coords.y].id == ARROW || map[coords.x][coords.y].id == FIRE) {
				death = true;
			}
		}

		return death;
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
			
			if (!(coords == previous_coords)) {
				if (!(coords == commands::pos(exit))) {
					std::cout << "You try to move that way, but something draws you into the cave" << std::endl;
					coords = previous_coords;
				}
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
		commands::pos previous_coords = { 10, 10 };
		commands::pos chest = { 0, 2 };
		commands::pos exit = { 1, -1 };
		commands::pos walls[1] = { 2, 2 };
		
		while (true) {

			std::cout << "\n   CAVE" << std::endl;
			display(coords, previous_coords, caveSizeX, caveSizeY);
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";
			
			item->shield = false;
			map[coords.x][coords.y] = { NONE };
			map[0][2] = { CHEST };
			
			previous_coords = coords;
			coords = command->userSpace(coords.x, coords.y);

			//Shield
			if (item->shield) {
				map[coords.x][coords.y] = { SHIELD };
			}

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
		int roomSizeX = 3;
		int roomSizeY = 3;

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
		else if (previous_room == ARROWDUNGEON) {
			coords = { 0, 1 };
		}
		else if (previous_room == DRAGONSROOM) {
			coords = { 2, 1 };
		}
		else {
			coords = { 1, 0 };
		}

		commands::pos previous_coords = { 10, 10 };
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
			display(coords, previous_coords, roomSizeX, roomSizeY);
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";

			item->shield = false;
			map[coords.x][coords.y] = { NONE };

			previous_coords = coords;
			coords = command->userSpace(coords.x, coords.y);

			//Shield
			if (item->shield) {
				map[coords.x][coords.y] = { SHIELD };
			}

			//End while loop with this condition-----------------------------------
			if (coords == commands::pos(exit_S) || coords == commands::pos(exit_N) || coords == commands::pos(exit_E) || coords == commands::pos(exit_W)) {
				break;
			}
			//---------------------------------------------------------------------

			if (!(coords == previous_coords)) {
				
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
		}
		if (coords == commands::pos(exit_N)) {
			room_status = CAVE;
		}
		else if (coords == commands::pos(exit_S)) {
			room_status = SHOP;
		}
		else if (coords == commands::pos(exit_E)) {
			room_status = DRAGONSROOM;
		}
		else {
			room_status = ARROWDUNGEON;
		}
	}

	inline void dragonsRoom() {
		int roomSizeX = 10;
		int roomSizeY = 5;
		int fireX1 = 9;
		int fireX2 = 13;
		int fireY = 2;
		

		setup_map(roomSizeX, roomSizeY);
		west_bound[2] = { DOOR };
		east_bound[2] = { DRAGON };
		
		commands::pos coords = { 0, 2 };
		commands::pos previous_coords = { 10, 10 };
		commands::pos exit = { -1, 2 };
		commands::pos kill_spot = { 9, 2 };

		while (true) {
			//Fireballs
			if (fireX1 <= 9 && fireX1 >= 0) {
				map[fireX1][fireY] = { FIRE };
				map[fireX1][fireY + 1] = { FIRE };
				map[fireX1][fireY + 2] = { FIRE };
			}
			if (fireX1 <= 8 && fireX1 >= -1) {
				map[fireX1 + 1][fireY] = { FIRE };
				map[fireX1 + 1][fireY + 1] = { FIRE };
				map[fireX1 + 1][fireY + 2] = { FIRE };
			}
			if (fireX1 <= 7 && fireX1 >= -2) {
				map[fireX1 + 2][fireY] = { FIRE };
				map[fireX1 + 2][fireY + 1] = { FIRE };
				map[fireX1 + 2][fireY + 2] = { FIRE };
			}
			if (fireX1 <= -1) {
				map[fireX1 + 10][fireY] = { FIRE };
				map[fireX1 + 10][fireY + 1] = { FIRE };
				map[fireX1 + 10][fireY + 2] = { FIRE };
			}
			if (fireX1 == -2) {
				map[fireX1 + 11][fireY] = { FIRE };
				map[fireX1 + 11][fireY + 1] = { FIRE };
				map[fireX1 + 11][fireY + 2] = { FIRE };
			}
			if (fireX2 <= 9 && fireX2 >= 0) {
				map[fireX2][fireY] = { FIRE };
				map[fireX2][fireY - 1] = { FIRE };
				map[fireX2][fireY - 2] = { FIRE };
			}
			if (fireX2 <= 8 && fireX2 >= -1) {
				map[fireX2 + 1][fireY] = { FIRE };
				map[fireX2 + 1][fireY - 1] = { FIRE };
				map[fireX2 + 1][fireY - 2] = { FIRE };
			}
			if (fireX2 <= 7 && fireX2 >= -2) {
				map[fireX2 + 2][fireY] = { FIRE };
				map[fireX2 + 2][fireY - 1] = { FIRE };
				map[fireX2 + 2][fireY - 2] = { FIRE };
			}
			if (fireX2 <= -1) {
				map[fireX2 + 10][fireY] = { FIRE };
				map[fireX2 + 10][fireY - 1] = { FIRE };
				map[fireX2 + 10][fireY - 2] = { FIRE };
			}
			if (fireX2 == -2) {
				map[fireX2 + 11][fireY] = { FIRE };
				map[fireX2 + 11][fireY - 1] = { FIRE };
				map[fireX2 + 11][fireY - 2] = { FIRE };
			}
			
			fireX1 -= 1;
			fireX2 -= 1;

			if (fireX1 == -3) {
				fireX1 = 7;
			}
			if (fireX2 == -3) {
				fireX2 = 7;
			}

			//Shield
			if (item->shield) {
				map[coords.x][coords.y] = { SHIELD };
			}

			std::cout << "\n   DRAGON'S LAIR" << std::endl;
			if (display(coords, previous_coords, roomSizeX, roomSizeY)) {
				std::cout << "You got burnt to a crisp and died....\n\n\n\n\n\n\n\n" << std::endl;
				item->end = true;
				break;
			}

			item->shield = false;
			map[coords.x][coords.y] = { NONE };

			previous_coords = coords;
			coords = command->userSpace(coords.x, coords.y);

			setup_map(roomSizeX, roomSizeY);
			west_bound[2] = { DOOR };
			east_bound[2] = { DRAGON };

			//End while loop with this condition-----------------------------------
			if (coords == commands::pos(exit)) {
				break;
			}
			//---------------------------------------------------------------------

			//Kill Dragon
			if (coords == commands::pos(kill_spot) && item->dragon_blade) {
				std::cout << "You slayed the Dragon!!!!!\n\nYOU WIN\n\n\n\n\n" << std::endl;
				item->end = true;
				break;
			}

			if (!(coords == previous_coords)) {

				if (coords.x == roomSizeX || coords.y == roomSizeY || coords.x < 0 || coords.y < 0) {

					if (!(coords == commands::pos(exit))) {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}
			}
		}
		previous_room = DRAGONSROOM;
		room_status = CROSSROADS;
	}

	inline void arrowDungeon() {
		int roomSizeX = 8;
		int roomSizeY = 5;
		int arrowX = 0;
		int arrowY = 2;

		setup_map(roomSizeX, roomSizeY);
		east_bound[2] = { DOOR };
		map[0][2] = { CHEST };
		
		commands::pos coords = { 7, 2 };
		commands::pos previous_coords = { 10, 10 };
		commands::pos exit = { 8, 2 };
		commands::pos chest = { 0, 2 };

		while (true) {
			if (arrowX > 0 && arrowX < 2) {
				map[arrowX][arrowY] = { ARROW };
				map[arrowX - 1][arrowY + 1] = { ARROW };
				map[arrowX - 1][arrowY - 1] = { ARROW };
			}
			else if (arrowX >= 2 && arrowX < 8) {
				map[arrowX][arrowY] = { ARROW };
				map[arrowX - 1][arrowY + 1] = { ARROW };
				map[arrowX - 2][arrowY + 2] = { ARROW };
				map[arrowX - 1][arrowY - 1] = { ARROW };
				map[arrowX - 2][arrowY - 2] = { ARROW };
			}
			else if (arrowX == 8) {
				map[arrowX - 1][arrowY + 1] = { ARROW };
				map[arrowX - 2][arrowY + 2] = { ARROW };
				map[arrowX - 1][arrowY - 1] = { ARROW };
				map[arrowX - 2][arrowY - 2] = { ARROW };
			}
			else if (arrowX == 9) {
				map[arrowX - 2][arrowY + 2] = { ARROW };
				map[arrowX - 2][arrowY - 2] = { ARROW };

				arrowX = 1;
				map[arrowX][arrowY] = { ARROW };
				map[arrowX - 1][arrowY + 1] = { ARROW };
				map[arrowX - 1][arrowY - 1] = { ARROW };
			}

			arrowX += 1;

			//Shield
			if (item->shield) {
				map[coords.x][coords.y] = { SHIELD };
			}

			std::cout << "\n   ARROW DUNGEON" << std::endl;
			if (display(coords, previous_coords, roomSizeX, roomSizeY)) {
				std::cout << "You got hit by an arrow and died....\n\n\n\n\n\n\n\n" << std::endl;
				item->end = true;
				break;
			}
			std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";

			item->shield = false;
			map[coords.x][coords.y] = { NONE };

			setup_map(roomSizeX, roomSizeY); //This is here so map clears arrows
			east_bound[2] = { DOOR };
			map[0][2] = { CHEST };
			
			previous_coords = coords;
			coords = command->userSpace(coords.x, coords.y);

			//End while loop with this condition-----------------------------------
			if (coords == commands::pos(exit)) {
				break;
			}
			//---------------------------------------------------------------------

			if (!(coords == previous_coords)) {

				//Chest
				if (coords == commands::pos(chest)) {
					item->arrow_chest_proximity = true;
					std::cout << "You see a chest in front of you" << std::endl;
				}
				else {
					item->arrow_chest_proximity = false;
				}

				if (coords.x == roomSizeX || coords.y == roomSizeY || coords.x < 0 || coords.y < 0) {

					if (!(coords == commands::pos(exit))) {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}
			}
		}
		previous_room = ARROWDUNGEON;
		room_status = CROSSROADS;
	}

	inline void shop() {
		int roomSizeX = 1;
		int roomSizeY = 3;

		setup_map(roomSizeX, roomSizeY);
		north_bound[0] = { DOOR };
		map[0][0] = { STORE };

		commands::pos coords = { 0, 2 };
		commands::pos previous_coords = { 10, 10 };
		commands::pos exit = { 0, 3 };
		commands::pos store = { 0, 0 };

		while (true) {
			
			if (item->shop == false) {
				std::cout << "\n   SHOP" << std::endl;
				display(coords, previous_coords, roomSizeX, roomSizeY);
				std::cout << "\n                 (" << coords.x << "," << coords.y << ")\n\n";
			}

			item->shield = false;
			map[coords.x][coords.y] = { NONE };
			map[0][0] = { STORE };

			previous_coords = coords;
			coords = command->userSpace(coords.x, coords.y);

			//Shield
			if (item->shield) {
				map[coords.x][coords.y] = { SHIELD };
			}

			//End while loop with this condition-----------------------------------
			if (coords == commands::pos(exit)) {
				break;
			}
			//---------------------------------------------------------------------
			
			//STORE
			if (coords == commands::pos(store)) {
				item->shop = true;
				item->inventory();
				std::cout << "----------------------------" << std::endl;
				std::cout << "You've Entered Bryan's Shop!" << std::endl;
				std::cout << "Items for Sale:" << std::endl;
				for (int i = 0; i < item->store_items.size(); i++) {
					std::cout << item->store_items[i] << std::endl;
				}
				std::cout << "----------------------------\n\n\n\n\n\n\n\n" << std::endl;
			}
			else {
				item->shop = false;
			}

			if (!(coords == previous_coords)) {

				if (coords.x == roomSizeX || coords.y == roomSizeY || coords.x < 0 || coords.y < 0) {

					if (!(coords == commands::pos(exit))) {
						std::cout << "You hit a wall" << std::endl;
						coords = previous_coords;
					}
				}
			}
		}
		previous_room = SHOP;
		room_status = CROSSROADS;
	}
};