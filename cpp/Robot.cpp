#include "../headers/Robot.h"

#include <utility>
#include <cstdlib>
#include <ctime>
#include <iostream>

int Robot::Update() {
    if(mIndex >= 64){
        mIndex -= 64;
    }
    mIndex++;
    switch(commands[mIndex]){
        case 0:
            return Go;

        case 1:
            direction++;
            fix_direction();
            return Nothing;
        case 2:
            direction--;
            fix_direction();
            return Nothing;
        case 3:
            return Eating;
        case 4:
            return Watch;
        case 5:
            return Poising;
        default:
            mIndex+=commands[mIndex]-5;
            return 0;

    }

}
Robot::Robot(int iHealth, std::vector<int> iCommand): Base(iHealth, iCommand){
    type = "Robot";
}