#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>>field(64, vector<int>(64));

enum Type { Void, Food, Poison, Wall, Crt };
enum Action{Nothing, Left, Right, Up, Down};

class Robot
{
	Type _type;
private:
	int mHealht;
	int mDirection;
	int mIndex;
	
public:
	vector<int>commands;
	int update()
	{
		if (mIndex == commands.size()) mIndex = 0;
		switch (mIndex)
		{
		case (1):
			return Left;
		case (2):
			return Right;
		case (3):
			return Up;
		case (4):
			return Down;

			break;
		}
	}
};

int main()
{

	return 0;
}
