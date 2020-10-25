#include <iostream>
#include <vector>

using namespace std;

enum Action{Nothing, Go, Eat};

class Robot
{
private:
	
	int mDirection = 4;
	int mIndex = 0;

	int dir() {
		if (mDirection > 4){
			mDirection = 1;
		}
		else if (mDirection < 1){
			mDirection = 4;
		}

	}
	
public:
	vector<int>commands;
	int mHealht;
	int update()
	{
		/*if (mIndex == commands.size()) mIndex = 0;*/
		if (mIndex > 64) mIndex -= 64;
		switch (mIndex)
		{
		case (1):
			mDirection--;
			dir();
			return Nothing;

		case (2):
			mDirection++;
			dir();
			return Nothing;

		case (3):
			return Go;

		case(4):
			return Eat;

		case(5):
			mIndex += 5;
			return Nothing;
		}
	}
};

int main()
{

	return 0;
}
