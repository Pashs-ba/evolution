//
// Created by pashs on 10/27/20.
//

#ifndef EVO_HOLE_H
#define EVO_HOLE_H

#include "enums.h"
#include "Robot.h"
#include <utility>
#include <set>

class Hole {
private:
    std::pair<int, int> size;
    std::set<std::pair<int, int>> eat;
    int Eat_per_step;
    int minR;
    void generate_new_eat();
    static std::pair<int, int> find_direction(int r_dir);
    void step();
public:
    std::vector<Robot> robots;
    Hole(std::pair<int, int> size, int RCount,int commands_size, int RHealth, int Eat_per_step, int minR);
    void main();
};


#endif //EVO_HOLE_H
