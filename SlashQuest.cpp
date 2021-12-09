#include <iostream>
#include <string>
#include <algorithm>

int main(){

	std::cout << "SLASH QUEST - BRYAN LECZA" << std::endl;
	std::cout << "DECEMBER 9, 2021" << std::endl << std::endl;
	
	std::string name;
	std::cout << "Enter your character's name: ";
	std::getline(std::cin, name);
	transform(name.begin(), name.end(), name.begin(), ::toupper);
	
	std::cout << "Hello " << name << ", Welcome to Slash Quest" << std::endl;
	

}