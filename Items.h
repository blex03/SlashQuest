#pragma once
#include <iostream>


class items{

public:

	//Cave Items
	bool cave_chest = false;
	bool chest_proximity = false;

	//Shop
	bool shop = false;

	//Inventory items
	int gold_amount = 0;

	inline void inventory() {
		std::cout << "-------------" << std::endl;
		std::cout << "Gold: " << gold_amount << std::endl;
		std::cout << "-------------" << std::endl;
	}


};