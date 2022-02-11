#include "Command.h"

void Command::assignmentExp(std::vector<std::string> instruction)
{
	if (instruction[0][0] == 'w') {
		this->W = stof(instruction[2]);
	}
	if (instruction[0][0] == 'x') {
		this->X = stof(instruction[2]);
	}
	if (instruction[0][0] == 'y') {
		this->Y = stof(instruction[2]);
	}
	if (instruction[0][0] == 'z') {
		this->Z = stof(instruction[2]);
	}
}

