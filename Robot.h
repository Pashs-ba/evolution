#ifndef EVO_ROBOT_H
#define EVO_ROBOT_H
#include <vector>
#include "enums.h"
#include "Prim.h"

class Robot: Prim {
private:

    int mDirection = 4;
    int mIndex = 0;
    int fix_direction();
public:
    std::vector<int>commands;

}

#endif //EVO_ROBOT_H
