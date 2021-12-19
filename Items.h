#pragma once
#include <iostream>


class items{

public:

	//Cave Items
	bool cave_chest = false;
	bool chest_proximity = false;


	//Inventory items
	int gold_amount = 0;

	inline void inventory() {
		std::cout << "Gold: " << gold_amount << std::endl;
	}


};