#include "Robot.h"

int Robot::fix_direction(){
    if (mDirection > 4){
        mDirection = 1;
    }
    else if (mDirection < 1){
        mDirection = 4;
    }
}

int Robot::update(){

    if (mIndex > 64) mIndex -= 64;
    switch (mIndex)
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
            mIndex += 5;
            return Nothing;
    }
}

