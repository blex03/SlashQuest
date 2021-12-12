#pragma once 
#include <iostream>
#include "commands.h"

class rooms {
	
	private:
		commands* command = new commands();
	
	
	public:
		
		inline void cave(){
		
			commands::pos coords = {1,0};
		
		
			while(coords.x != 1 || coords.y != -1){
				
				coords = command->userSpace(coords.x, coords.y);
				
				if(coords.x < 0){
					std::cout << "You ran into a wall" << std::endl;
					coords.x++;
				}	
				
				if(coords.x > 2){
					std::cout << "You ran into a wall" << std::endl;
					coords.x--;
				}
				
				if(coords.y < 0 && coords.x != 1){
					std::cout << "You ran into a wall" << std::endl;
					coords.y++;
				}
				
				if(coords.y > 2){
					std::cout << "You ran into a wall" << std::endl;
					coords.y--;
				}	
				
				std::cout << "X: " << coords.x << std::endl;
				std::cout << "Y: " << coords.y << std::endl;
					
			}
		
}
	
};