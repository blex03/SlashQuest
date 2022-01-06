#pragma once
#include <iostream>
#include "Items.h"
#include "TextParsing.h"

items* item = new items();
text* parse = new text();

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

	inline void instructions() {

		std::cout << std::endl;
		std::cout << "--------------------------------------------------------------" << std::endl;
		std::cout << "INSTRUCTIONS" << std::endl;
		std::cout << "Type in cardinal directions to move (NORTH, SOUTH, EAST, WEST) or (N, S, E, W)" << std::endl;
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
	inline pos userSpace(int x, int y) {

		std::string command;

		std::cout << "\n>>> ";
		std::getline(std::cin, command);
		command = parse->lowerCase(command);
		std::cout << std::endl;

		parse->parsing(command);
		std::string order = parse->order;
		std::string object = parse->object;

		//inventory
		if (order == "inventory") {
			item->inventory();
		}

		//Instructions
		else if (order == "?") {
			instructions();
		}

		//Directions
		else if (order == "north" || order == "n") {
			y++;
		}
		else if (order == "south" || order == "s") {
			y--;
		}
		else if (order == "east" || order == "e") {
			x++;
		}
		else if (order == "west" || order == "w") {
			x--;
		}

		//Open
		else if (order == "open") {
			if (object == "chest") {
				if (item->chest_proximity == true && item->cave_chest == false) {
					std::cout << "You opened the chest!" << std::endl;
					std::cout << "Inside was a sack of coins" << std::endl;
					std::cout << "You've earned 100G" << std::endl;
					item->gold_amount += 100;
					item->cave_chest = true;
				}
				else if (item->chest_proximity == true && item->cave_chest == true) {
					std::cout << "The chest is empty" << std::endl;
				}

				else if (item->chest_proximity == false) {
					std::cout << "What chest?" << std::endl;
				}
			}
			else if (object == "") {
				std::cout << "Open what?" << std::endl;
			}
			else {
				std::cout << "You can't open \"" << object << "\" in Slash Quest" << std::endl;
			}
		}

		//Use
		else if (order == "use") {
			if (object == "placeholder") {
				std::cout << "Thumbs up" << std::endl;
			}
			else if (object == "") {
				std::cout << "Use what?" << std::endl;
			}
			else {
				std::cout << "You can't use \"" << object << "\" in Slash Quest" << std::endl;
			}
		}

		//Buy
		else if (order == "buy") {
			if (item->shop == true) {
				if (object == "shield") {
					if (find(item->store_items.begin(), item->store_items.end(), ">> Shield -- 100G") != item->store_items.end()) {
						if (item->gold_amount >= 100) {
							item->store_items.erase(std::remove(item->store_items.begin(), item->store_items.end(), ">> Shield -- 100G"), item->store_items.end());
							item->your_items.push_back("Shield");
							item->gold_amount -= 100;
						}
						else {
							std::cout << "You don't have enough money to buy the Shield" << std::endl;
						}
					}
					else {
						std::cout << "There are no more shields left" << std::endl;
					}
				}

				else if (object == "dragon-blade") {
					if (find(item->store_items.begin(), item->store_items.end(), ">> Dragon-Blade -- 600G") != item->store_items.end()) {
						if (item->gold_amount >= 600) {
							item->store_items.erase(std::remove(item->store_items.begin(), item->store_items.end(), ">> Dragon-Blade -- 600G"), item->store_items.end());
							item->your_items.push_back("Dragon-Blade");
							item->gold_amount -= 600;
						}
						else {
							std::cout << "You don't have enough money to buy the Dragon-Blade" << std::endl;
						}
					}
					else {
						std::cout << "There are no more dragon-blades left" << std::endl;
					}
				}
				else {
					std::cout << "This shop doesn't sell " << object << "s" << std::endl;
				}
			}
			else {
				std::cout << "Transactions cannot be made outside of a shop" << std::endl;
			}
		}

		//Sell
		else if (order == "sell") {
			if (item->shop == true) {
				if (object == "shield") {
					if (find(item->your_items.begin(), item->your_items.end(), "Shield") != item->your_items.end()) {
						item->your_items.erase(std::remove(item->your_items.begin(), item->your_items.end(), "Shield"), item->your_items.end());
						item->store_items.push_back(">> Shield -- 100G");
						item->gold_amount += 100;
					}
					else {
						std::cout << "You don't have any shields" << std::endl;
					}
				}
				else if (object == "dragon-blade") {
					if (find(item->your_items.begin(), item->your_items.end(), "Dragon-Blade") != item->your_items.end()) {
						item->your_items.erase(std::remove(item->your_items.begin(), item->your_items.end(), "Dragon-Blade"), item->your_items.end());
						item->store_items.push_back(">> Dragon-Blade -- 600G");
						item->gold_amount += 600;
					}
					else {
						std::cout << "You don't have any dragon blades" << std::endl;
					}
				}
				else {
					std::cout << "You don't have any " << object << "s" << std::endl;
				}
			}
			else {
				std::cout << "Transactions cannot be made outside of a shop" << std::endl;
			}
		}
		else {
		std::cout << "Invalid Command!" << std::endl;
		}

		return { x,y };
	}
};