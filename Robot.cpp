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

    if (mIndex > size) mIndex -= size;
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
    return Nothing;
}
Robot::Robot(int commands_size, int health):
    commands(commands_size)
{
    mHealth = health;
    size = commands_size;
}

