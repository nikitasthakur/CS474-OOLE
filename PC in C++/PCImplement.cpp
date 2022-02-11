#include "PCImplement.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <string>
using namespace std;

PCImplement::PCImplement(std::vector<std::string> instructions) {

	this->W = 0;
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
	this->Curr_Instruction = 0;
	this->fileInstructions = instructions;
}

std::vector<std::string> PCImplement::convertInstruction(string instruction)
{
	instruction.pop_back();
	istringstream iss(instruction);
	std::vector<std::string> tokens{ istream_iterator<string>{iss}, istream_iterator<string>{}};
	std::vector<std::string> instructionArray;

	if (tokens.size() == 5) {

		instructionArray.push_back(tokens[0]);
		instructionArray.push_back(to_string(this->getRegisterValue(tokens[2][0])));
		instructionArray.push_back(tokens[3]);
		if (isalpha(tokens[4][0]))
			instructionArray.push_back(to_string(this->getRegisterValue(tokens[4][0])));
		else
			instructionArray.push_back(tokens[4]);
	}


	if (tokens.size() == 3)
	{
		return tokens;
	}

	return instructionArray;
};

float PCImplement::getW()
{
	return this->W;
}

float PCImplement::getX()
{
	return this->X;
}

float PCImplement::getY()
{
	return this->Y;
}

float PCImplement::getZ()
{
	return this->Z;
}

void PCImplement::setW(float value)
{
	this->W = value;
}

void PCImplement::setX(float value)
{
	this->X = value;
}

void PCImplement::setY(float value)
{
	this->Y = value;
}


void PCImplement::setZ(float value)
{
	this->Z = value;
}


float PCImplement::getRegisterValue(char reg)
{
	if (reg == 'w')
		return this->getW();
	if (reg == 'x')
		return this->getX();
	if (reg == 'y')
		return this->getY();
	if (reg == 'z')
		return this->getZ();
	return -1;
}

void PCImplement::setRegisterValue(char reg, float value)
{
	if (reg == 'w')
		this->setW(value);
	if (reg == 'x')
		this->setX(value);
	if (reg == 'y')
		this->setY(value);
	if (reg == 'z')
		this->setZ(value);
}

void PCImplement::arithmeticExp(std::vector<std::string> instruction)
{
	float result = -1.0;

	if (instruction[2].compare("+") == 0)
		result = stof(instruction[1]) + stof(instruction[3]);

	if (instruction[2].compare("-") == 0)
		result = stof(instruction[1]) - stof(instruction[3]);

	if (instruction[2].compare("*") == 0)
		result = stof(instruction[1]) * stof(instruction[3]);

	if (instruction[2].compare("**") == 0)
		result = pow(stof(instruction[1]),stof(instruction[3]));

	if (instruction[2].compare("/") == 0)
		result = stof(instruction[1]) / stof(instruction[3]);

	this->setRegisterValue(instruction[0][0], result);
	this->Curr_Instruction += 1;
}

void PCImplement::jumpExp(std::vector<std::string> instruction)
{
	float regValue = this->getRegisterValue(instruction[0][0]);

	if (regValue != 0)
		this->Curr_Instruction = stoi(instruction[2]) - 1;
	else
		this->Curr_Instruction += 1;
}