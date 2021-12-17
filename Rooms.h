#pragma once 
#include <iostream>
#include "commands.h"

class rooms {
	
private:
	commands* command = new commands();
	
	
public:
		
	inline void cave(){
		
		commands::pos coords = {1,0};

		
		
		//wall coordinates
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

		int initial_boundaries[3][2] = {
										{1, -1},
										{-1, 0},
										{2, 0}
		};
		
		
		while(coords.x != 1 || coords.y != 5){
				
			coords = command->userSpace(coords.x, coords.y);
			
			//Checks if player reached a boundary
			for (int i = 0; i < 11; i++) {
				if (coords.x == wall_boundaries[i][0] && coords.y == wall_boundaries[i][1]) {
					std::cout << "You ran into a wall" << std::endl;
				}
			}

			for (int i = 0; i < 3; i++) {
				if (coords.x == initial_boundaries[i][0] && coords.y == initial_boundaries[i][1]) {
					std::cout << "You try to move that way but your body is drawn to the cave" << std::endl;
					coords = {1, 0};
				}
			}

			if(coords.x < 0){
				coords.x++;
			}		
			if(coords.x > 2){
				coords.x--;
			}	
			if(coords.y < 0 && coords.x != 1){
				coords.y++;
			}	
			if(coords.y > 3){
				coords.y--;
			}	
			
			std::cout << std::endl;
			std::cout << "X: " << coords.x << std::endl;
			std::cout << "Y: " << coords.y << std::endl;
					
		}
		
}
	
};