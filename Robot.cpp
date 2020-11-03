#include "Robot.h"

#include <utility>
#include <cstdlib>
#include <ctime>
#include <iostream>


void Robot::fix_direction(){
    if (mDirection > 4){
        mDirection = 1;
    }
    else if (mDirection < 1){
        mDirection = 4;
    }

}

int Robot::update(){
    mIndex++;
    if (mIndex >= commands.size() - 1 ){
        mIndex -= commands.size()-1;
    }
    if (!commands.empty()){
        switch (commands[mIndex])
        {
            case (1): // Left
                mDirection--;
                fix_direction();

                return Nothing;

            case (2): // Right
                mDirection++;
                fix_direction();

                return Nothing;

            case (3):
                return Go;

            case(4):
                return Eat;

            case(5):
                mIndex += 1;
                return Nothing;
            case(6):
                mIndex += 2;
                return Nothing;
            case(7):
                mIndex += 3;
                return Nothing;
            case(8):
                mIndex += 4;
                return Nothing;
            case(9):
                mIndex += 5;
                return Nothing;
			case(10):
				//std::cout << "Repoison" << std::endl;
				return Poison;
            case(11):
                return Watch;
        }
//        if (mIndex >10){
//            mIndex += mIndex - 11;
//        }
    }


    return Nothing;
}

Robot::Robot(int commands_size, int health, std::pair<int, int> iCoordinates):
    commands(commands_size),
    mCoordinates(std::move(iCoordinates))
{
    mHealth = health;
    size = commands_size;
//    srand (time(NULL));
    for(auto& i: commands){
		i = 1+rand()%12;
    }
}

