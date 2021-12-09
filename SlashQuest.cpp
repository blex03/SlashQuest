#include <iostream>
#include <string>
#include <algorithm>

void instructions(){
	using namespace std;
	
	cout << endl;
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

namespace room1{
	int x = 0;
	int y = 3;
}

/*
This is where the player will be able to input commands.
It will run as long as the user hasn't reached the end of the room.
The end of the room is specified by the userSpace's parameters
*/
void userSpace(int finalX, int finalY){
	int positionX = 0;
	int positionY = 0;
	
	
	while(positionX != finalX || positionY != finalY){
		std::string command;
		
		std::cout << "\n\n>>> ";
		std::getline(std::cin, command);
		command = lowerCase(command);
		
		if(command == "?"){
			instructions();
		}
		else if(command == "north"){
			positionY++;
		}
		else if(command == "south"){
			positionY--;
		}
		else if(command == "east"){
			positionX++;
		}
		else if(command == "west"){
			positionX--;
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
	
	userSpace(room1::x, room1::y);
	
	std::cout << "\nIt worked!!!\n";
	
	
	
}