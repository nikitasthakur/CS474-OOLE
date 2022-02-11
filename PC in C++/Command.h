#include <string>
#include <vector>
using namespace std;

class Command
{
protected:
	float W = 0;
	float X = 0;
	float Y = 0;
	float Z = 0;

public:
	Command() {};
	virtual void arithmeticExp(std::vector<std::string>) = 0;
	virtual void jumpExp(std::vector<std::string>) = 0;
	void assignmentExp(std::vector<std::string>);

	virtual ~Command() {};
};

