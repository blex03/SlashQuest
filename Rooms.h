#pragma once 
#include <iostream>
#include "commands.h"

class rooms {

private:
	commands* command = new commands();


public:

	inline void cave() {

		commands::pos coords = { 1,0 };

		//boundary coordinates
		int initial_boundaries[3][2] = {
										{1, -1},
										{-1, 0},
										{2, 0}
		};

		int wall_boundaries[11][2] = {
										{0, 0},
										{2, 0},
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

	

		while (coords.x != 1 || coords.y != 5) {

			//So player will backtrack when they hit a boundary
			//Can also compare previous_coords to coords to track direction player is moving
			commands::pos previous_coords = coords;

			coords = command->userSpace(coords.x, coords.y);


			//Checks if player reached a boundary
			//Why doesn't "coords == {initial_boundaries[i][0], initial_boundaries[i][1]}" work?
			for (int i = 0; i < 3; i++) {
				if (coords.x == initial_boundaries[i][0] && coords.y == initial_boundaries[i][1]) {
					std::cout << "You try to move that way but your body is drawn towards the cave" << std::endl;
					coords = previous_coords;
				}
			}

			for (int i = 0; i < 11; i++) {
				if (coords.x == wall_boundaries[i][0] && coords.y == wall_boundaries[i][1]) {
					std::cout << "You ran into a wall" << std::endl;
					coords = previous_coords;
				}
			}


			//cave entry
			//see if alden comes up with a solution for this top line
			if (coords.x == 1 && coords.y == 1 && previous_coords.y < 1) {

				std::cout << "You have entered the cave. You see something shiny in the northwest corner" << std::endl;
			}

			//cave exit
			if (coords.x == 1 && coords.y == 0 && previous_coords.y > 0) {

				std::cout << "You left the cave" << std::endl;
			}

			//chest
			if (coords.x == 0 && coords.y == 3) {

				std::cout << "You see a chest in front of you" << std::endl;
				coords = previous_coords;
			}



			std::cout << std::endl;
			std::cout << "                                       X: " << coords.x << std::endl;
			std::cout << "                                       Y: " << coords.y << std::endl;

		}

	}

};