//
// Created by pashs on 10/27/20.
//

#ifndef EVO_HOLE_H
#define EVO_HOLE_H

#include "enums.h"
#include "Robot.h"
#include <utility>

class Hole {
private:
    std::pair<int, int> size;
    std::vector<std::pair<int, int>> eat;
    int Eat_per_step;
public:
    std::vector<Robot> robots;
    Hole(std::pair<int, int> size, int RCount,int commands_size, int RHealth, int Eat_per_step);
    void main();
};


#endif //EVO_HOLE_H
