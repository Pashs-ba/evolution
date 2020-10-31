//
// Created by pashs on 10/27/20.
//

#ifndef EVO_FIELD_H
#define EVO_FIELD_H

#include "enums.h"
#include "Robot.h"
#include <utility>
#include <set>

class Field {
private:
    int Eat_per_step;
    int r_count;
    void generate_new_eat();
    static std::pair<int, int> find_direction(int r_dir);

public:
    int minR;
    void step();
    std::vector<Robot> robots;
    Field(std::pair<int, int> size, int RCount, int commands_size, int RHealth, int Eat_per_step, int minR);
    std::pair<int, int> size;
    std::vector<std::pair<int, int>> eat;
    void new_era();
};


#endif //EVO_FIELD_H
