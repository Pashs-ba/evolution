#ifndef EVO_ROBOT_H
#define EVO_ROBOT_H
#include <vector>
#include "enums.h"
#include <random>


class Robot{
private:

    int mDirection = 4;
    int mIndex = 0;
    int fix_direction();
    int size;

public:
    std::vector<int> commands;
    int update();
    int mHealth = 100;
    std::pair<int, int> mCoordinates;
    Robot(int commands_size, int health, std::pair<int, int> iCoordinates);
};

#endif //EVO_ROBOT_H
