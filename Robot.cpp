#include "Robot.h"

#include <utility>

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

Robot::Robot(int commands_size, int health, std::pair<int, int> iCoordinates):
    commands(commands_size),
    mCoordinates(std::move(iCoordinates))
{
    mHealth = health;
    size = commands_size;

    std::random_device c;
    std::default_random_engine c1(c());
    std::uniform_int_distribution<int> make_c(0, 5);
    for(auto& i: commands){
        i = make_c(c1);
    }
}

