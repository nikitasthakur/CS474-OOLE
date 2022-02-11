#include "Instruction.h"
#include "PCImplement.h"
#include <iostream>
#include <fstream>
using namespace std;

class Type12 : Instruction
{
	PCImplement *pc;
	std::vector<std::string> x;

	public:
		Type12(PCImplement *p, std::vector<std::string> abc)
		{
			pc = p;
			x = abc;
		}

	void run();
};

void Type12::run()
{
	pc->arithmeticExp(x);
}

class Type34 : Instruction
{
	PCImplement *pc;
	std::vector<std::string> x;

public:
	Type34(PCImplement *p, std::vector<std::string> abc)
	{
		pc = p;
		x = abc;
	}

	void run();
};

void Type34::run()
{
	pc->jumpExp(x);
}

void printRegisters(PCImplement *p, int f)
{
	cout << "\t__________________________" << endl;
	cout << "\t    Register contents:" << endl << endl;
	cout << endl << "\tRegister W: " << p->getW() << endl;
	cout << "\tRegister X: " << p->getX() << endl;
	cout << "\tRegister Y: " << p->getY() << endl;
	cout << "\tRegister Z: " << p->getZ() << endl;
	int l = p->Curr_Instruction;
	int pl = l;
	if (l + 1 > f)
		pl = 0;
	cout << endl << "\tNext Instruction Index:" << pl + 1 << endl;
	cout << "\t__________________________" << endl;
}

void printFile(std::vector<std::string> file, PCImplement* p)
{
	cout << "\t___________________________________________" << endl;
	cout << "\t\t File Instruction Sequence:" << endl << endl;
	for (int i = 0; i < file.size(); i++)
	{
		cout << "\t" << (i + 1) << ": " << file[i] << endl;
	}
	printRegisters(p, file.size());
	cout << "\t___________________________________________" << endl;
}

int main()
{
	std::string inputcmd = "q";
	const int n_cmd = 3;
	bool flag = false;
	int commandsExec = 0;
	std::vector<std::string> fileLines;
	PCImplement *pcInstance;
	int filesize = 0;

	string fileName = "pc_input.txt";
	string lineRead;
	ifstream myfile;
	myfile.open(fileName);
	if (!myfile) {
		cout << endl << "\tFile does not exist!!!" << endl;
	}
	while (getline(myfile, lineRead))
	{
		fileLines.push_back(lineRead);
	}
	pcInstance = new PCImplement(fileLines);
	flag = true;
	filesize = fileLines.size();

	cout << endl << "*******************Programmable Calculator in cpp by Nikita Thakur*******************" << endl;
	while (inputcmd[0] != 'x')
	{
		cout << "------------------------------------------------------" << endl;
		cout << "\ts - Execute next instruction" << endl;
		cout << "\tr - Run input file" << endl;
		cout << "\tx - Quit" << endl;
		cout << endl << "------------------------------------------------------" << endl;
		cout << endl << "  Input a command..." << endl;

		getline(cin, inputcmd);


		if (inputcmd[0] == 's')
		{
			if (pcInstance->Curr_Instruction < filesize)
			{
				
				std::vector<std::string> parsedInstr = pcInstance->convertInstruction(pcInstance->fileInstructions[pcInstance->Curr_Instruction]);

				cout << " Instruction Executed......:" << endl;
				cout << fileLines[pcInstance->Curr_Instruction]<< endl;

				if (parsedInstr.size() == 4)
				{
					
					Type12 stmt(pcInstance, parsedInstr);
					stmt.run();
				}
				if (parsedInstr.size() == 3 && parsedInstr[1][0] == '?')
				{
					Type34 stmt(pcInstance, parsedInstr);
					stmt.run();
				}
				if (parsedInstr.size() == 3 && parsedInstr[1][0] == '=')
				{	
					pcInstance->assignmentExp(parsedInstr);
					pcInstance->Curr_Instruction = pcInstance->Curr_Instruction + 1;
				}
				printRegisters(pcInstance, filesize);
			}
			else {
				pcInstance->Curr_Instruction = 0;
				vector<string> parsedInstr = pcInstance->convertInstruction(pcInstance->fileInstructions[pcInstance->Curr_Instruction]);
				if (parsedInstr.size() == 4)
				{
					Type12 stmt(pcInstance, parsedInstr);
					stmt.run();
				}
				if (parsedInstr.size() == 3 && parsedInstr[1][0] == '?')
				{
					Type34 stmt(pcInstance, parsedInstr);
					stmt.run();
				}
				if (parsedInstr.size() == 3 && parsedInstr[1][0] == '=')
				{
					pcInstance->assignmentExp(parsedInstr);
					pcInstance->Curr_Instruction += 1;
				}
				printRegisters(pcInstance, filesize);
			}
		}

		else if (inputcmd[0] == 'r')
		{
			while (commandsExec < 100)
			{
				if (pcInstance->Curr_Instruction < filesize)
				{
					std::vector<std::string> parsedInstr = pcInstance->convertInstruction(pcInstance->fileInstructions[pcInstance->Curr_Instruction]);
					
					if (parsedInstr.size() == 4)
					{
						Type12 stmt(pcInstance, parsedInstr);
						stmt.run();
					}

					if (parsedInstr.size() == 3 && parsedInstr[1][0] == '?')
					{
						Type34 stmt(pcInstance, parsedInstr);
						stmt.run();
					}

					if (parsedInstr.size() == 3 && parsedInstr[1][0] == '=')
					{
						pcInstance->assignmentExp(parsedInstr);
						pcInstance->Curr_Instruction += 1;
					}
					commandsExec++;
				}
				else
				{
					commandsExec = 0;
					printRegisters(pcInstance, filesize);
					delete pcInstance;
					pcInstance = new PCImplement(fileLines);
					break;
				}
			}

			if (commandsExec == 100)
			{
				cout << endl << "\t100 executions reached!!!" << endl;
				delete pcInstance;
				pcInstance = new PCImplement(fileLines);
			}
		}
	}

	return 0;
};