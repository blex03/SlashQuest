#include <iostream>
#include <string>
#include <algorithm>

void instructions(){
	using namespace std;
	
	cout << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "INSTRUCTIONS" << endl;
	cout << "Type in cardinal directions to move (NORTH, WEST, EAST, SOUTH)" << endl;
	cout << endl;
	cout << "*List of commands*" << endl;
	cout << ">open" << endl;
	cout << ">use" << endl;
	cout << ">buy" << endl;
	cout << ">sell" << endl;
	cout << endl;
	cout << "Enter '?' in order to print instructions" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << endl;
}

//make words either all uppercase or all lowercase
std::string upperCase(std::string command){
	transform(command.begin(), command.end(), command.begin(), ::toupper);
	return command;
}
std::string lowerCase(std::string command){
	transform(command.begin(), command.end(), command.begin(), ::tolower);
	return command;
}


//userSpace is where the player will be able to enter commands
void userSpace(int& x, int&y){
	
		std::string command;
		
		std::cout << "\n\n>>> ";
		std::getline(std::cin, command);
		command = lowerCase(command);
		
		if(command == "?"){
			instructions();
		}
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
	
}

void userSpace(int& x, int& y);

void firstCave(){
	
	int positionX = 1;
	int positionY = 0;
	
	while(positionX != 1 || positionY != -1){
		
		userSpace(positionX, positionY);
		
		if(positionX < 0){
			std::cout << "You ran into a wall" << std::endl;
			positionX++;
		}	
		
		if(positionX > 2){
			std::cout << "You ran into a wall" << std::endl;
			positionX--;
		}
		
		if(positionY < 0 && positionX != 1){
			std::cout << "You ran into a wall" << std::endl;
			positionY++;
		}
		
		if(positionY > 2){
			std::cout << "You ran into a wall" << std::endl;
			positionY--;
		}	
		
		std::cout << "X: " << positionX << std::endl;
		std::cout << "Y: " << positionY << std::endl;
			
	}
	
}

int main(){

	//Introduction
	std::cout << "SLASH QUEST - BRYAN LECZA" << std::endl;
	std::cout << "DECEMBER 9, 2021 \n\n";
	
	std::string name;
	std::cout << "Enter your character's name: ";
	std::getline(std::cin, name);
	name = upperCase(name);
	
	
	std::cout << "Hello " << name << ", Welcome to Slash Quest" << std::endl;
	
	instructions();
	
	std::cout << "You stand before a cave to your north. You're adventure starts here." << std::endl;
	
	firstCave();
	
	std::cout << "\nIt worked!!!\n";
	
	std::cin.get();
	
}