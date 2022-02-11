#include "Command.h"
using namespace std;

class PCImplement : public Command
{
public:
	PCImplement(vector<string>);
	int Curr_Instruction;
	void arithmeticExp(vector<string>);
	void jumpExp(vector<string>);
	vector<string> convertInstruction(string);
	vector<string> fileInstructions;

	void setW(float);
	void setX(float);
	void setY(float);
	void setZ(float);
	float getW();
	float getX();
	float getY();
	float getZ();

	float getRegisterValue(char);
	void setRegisterValue(char, float);

	virtual ~PCImplement() {};

};


