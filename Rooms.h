#pragma once 
#include <iostream>
#include "commands.h"

class rooms {

private:
	commands* command = new commands();
	


public:

	//So I can continue the while loop in the main function
	bool game_play = true;

	//This is so I can determine which room to call in the main function
	int room_status[2] = { 1, 0 };

	inline void cave() {

		commands::pos coords = { 1, 0 };

		//boundary coordinates
		int initial_boundaries[3][2] = {
										{1, -1},
										{0, 0},
										{2, 0}
		};

		int wall_boundaries[11][2] = {
										{-1, 1},
										{-1, 2},
										{-1, 3},
										{0, 4},
										{1, 4},
										{2, 4},
										{3, 3},
										{3, 2},
										{3, 1}
		};

		commands::pos chest = { 0, 3 };
		
		
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
			//Why doesn't "coords == {initial_boundaries[i][0], initial_boundaries[i][1]}" work?
			for (int i = 0; i < 3; i++) {
				if (coords == commands::pos::to_pos(initial_boundaries[i][0], initial_boundaries[i][1])) {
					std::cout << "You try to move, but your body is drawn towards the northern cave" << std::endl;
					coords = previous_coords;
				}
			}

			for (int i = 0; i < 11; i++) {
				if (coords == commands::pos::to_pos(wall_boundaries[i][0], wall_boundaries[i][1])) {
					std::cout << "You ran into a wall" << std::endl;
					coords = previous_coords;
				}
			}


			//cave entry
			if (coords == commands::pos::to_pos(1, 1) && previous_coords.y < 1) {

				std::cout << "You have entered the cave. You see something shiny in the northwest corner" << std::endl;
			}

			//cave exit
			if (coords == commands::pos::to_pos(1, 0) && previous_coords.y > 0) {

				std::cout << "You left the cave" << std::endl;
			}

			//chest
			if (coords == commands::pos::to_pos(0, 3)) {

				std::cout << "You see a chest in front of you waiting to be opened";

				item->chest_proximity = true;

				coords = previous_coords;
			}



			std::cout << std::endl;
			std::cout << "                                       X: " << coords.x << std::endl;
			std::cout << "                                       Y: " << coords.y << std::endl;

		}

		room_status[0] = 0;
		room_status[1] = 1;

	}

	inline void outside() {

		std::cout << "You made it outside!";
		game_play = false;
	}

};