#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class text {
public:

	//make words either all uppercase or all lowercase
	inline std::string upperCase(std::string command) {
		transform(command.begin(), command.end(), command.begin(), ::toupper);
		return command;
	}
	inline std::string lowerCase(std::string command) {
		transform(command.begin(), command.end(), command.begin(), ::tolower);
		return command;
	}
	
	std::string order; //(command phrase)
	std::string object;//In case user inputs two words ("open CHEST") where chest is the object
	
	inline void parsing(std::string command){
		order = "";
		object = "";

		for (size_t i = 0; i < command.length(); i++) {
			if (command[i] == ' ') {
				for (size_t j = i + 1; j < command.length(); j++) {
					object += command[j];
				}

				break;
			}
			order += command[i];
		}
	}
};
