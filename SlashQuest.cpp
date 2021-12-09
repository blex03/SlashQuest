#include <iostream>
#include <string>
#include <algorithm>

void instructions(){
	std::cout << "INSTRUCTIONS" << std::endl;
	std::cout << "Type in cardinal directions to move (NORTH, WEST, EAST, SOUTH)" << std::endl;
	std::cout << std::endl;
	std::cout << "*List of commands*" << std::endl;
	std::cout << ">open" << std::endl;
	std::cout << ">use" << std::endl;
	std::cout << ">buy" << std::endl;
	std::cout << ">sell" << std::endl;
	std::cout << std::endl;
	std::cout << "Enter '?' in order to print instructions" << std::endl;
}

int main(){

	//Introduction
	std::cout << "SLASH QUEST - BRYAN LECZA" << std::endl;
	std::cout << "DECEMBER 9, 2021 \n\n";
	
	std::string name;
	std::cout << "Enter your character's name: ";
	std::getline(std::cin, name);
	
	transform(name.begin(), name.end(), name.begin(), ::toupper); //Just capitilizes the persons name
	std::cout << "Hello " << name << ", Welcome to Slash Quest \n\n";
	
	instructions();
	
	
	
}