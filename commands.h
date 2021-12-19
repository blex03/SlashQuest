#pragma once
#include <iostream>
#include <string>
#include <algorithm>

#include "Items.h"

items* item = new items();


class commands {
	public:
		
		//pos is position
		struct pos {
			int x;
			int y;

			static pos to_pos(int x, int y) {
				return { x,y };
			}

			bool operator==(pos other) {
				return x == other.x && y == other.y;
			};
		};
				
		
		//make words either all uppercase or all lowercase
		inline std::string upperCase(std::string command){
			transform(command.begin(), command.end(), command.begin(), ::toupper);
			return command;
		}
		inline std::string lowerCase(std::string command){
			transform(command.begin(), command.end(), command.begin(), ::tolower);
			return command;
		}
		
		inline void instructions(){
			
			std::cout << std::endl;
			std::cout << "--------------------------------------------------------------" << std::endl;
			std::cout << "INSTRUCTIONS" << std::endl;
			std::cout << "Type in cardinal directions to move (NORTH, SOUTH, EAST, WEST)" << std::endl;
			std::cout << std::endl;
			std::cout << "*List of commands*" << std::endl;
			std::cout << ">open" << std::endl;
			std::cout << ">use" << std::endl;
			std::cout << ">buy" << std::endl;
			std::cout << ">sell" << std::endl;
			std::cout << std::endl;
			std::cout << "Enter 'Inventory' in order to open inventory" << std::endl;
			std::cout << "Enter '?' in order to print instructions" << std::endl;
			std::cout << "--------------------------------------------------------------" << std::endl;
			std::cout << std::endl;
		}	
		
		//userSpace is where the player will be able to enter commands
		inline pos userSpace(int x, int y){
	
			std::string command;
			
			std::cout << "\n\n>>> ";
			std::getline(std::cin, command);
			command = lowerCase(command);
			std::cout << std::endl;
			
			//inventory
			if (command == "inventory") {
				item->inventory();
			}

			//Instructions
			else if(command == "?"){
				instructions();
			}

			//Directions
			else if(command == "north"){
				y++;
			}
			else if(command == "south"){
				y--;
			}
			else if(command == "east"){
				x++;
			}
			else if(command == "west"){
				x--;
			}

			//Open chest
			else if (command == "open chest") {
				if (item->chest_proximity == true) {
					std::cout << "You opened the chest!" << std::endl;
					std::cout << "Inside was a sack of coins" << std::endl;
					std::cout << "You've earned 100g" << std::endl;
					item->gold_amount += 100;
					item->cave_chest = true;
				}
			}

			else {

				std::cout << "Invalid Command!";
			}
		
			return {x,y};
		}
		
		inline void cave_chest() {
			

		}
	
};