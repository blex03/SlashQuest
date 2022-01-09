#pragma once
#include <iostream>
#include <vector>

class items{
public:

	//Cave Items
	bool cave_chest = false;
	bool chest_proximity = false;
	
	//Arrow Dungeon
	bool arrow_chest = false;
	bool arrow_chest_proximity = false;
	bool death = false;

	//Shop
	bool shop = false;

	//Inventory items
	int gold_amount = 0;
	std::vector<std::string> store_items = { ">> Shield -- 100G", ">> Dragon-Blade -- 600G" };
	std::vector<std::string> your_items;

	bool shield = false;
	bool dragon_blade = false;

	inline void inventory() {
		std::cout << "-------------" << std::endl;
		std::cout << "Gold: " << gold_amount << std::endl;
		std::cout << std::endl;
		std::cout << "Your Items: " << std::endl;
		for (int i = 0; i < your_items.size(); i++) {
			std::cout << "-" << your_items[i] << std::endl;
		}
		std::cout << "-------------" << std::endl;
	}
};