#pragma once


class inventory{

public:
	int gold_amount = 0;

	inline void items() {
		std::cout << "Gold: " << gold_amount << std::endl;
	}


};