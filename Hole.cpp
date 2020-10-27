//
// Created by pashs on 10/27/20.
//

#include "Hole.h"
#include <utility>
#include <ctime>
#include <cstdlib>
#include <random>
#include <set>

Hole::Hole(std::pair<int, int> size, int RCount,int commands_size, int RHealth, int Eat_per_step):
    size(size),
    robots(RCount, Robot(commands_size, RHealth, coordinate{-1, -1}))
{
    std::random_device x;
    std::random_device y;
    std::default_random_engine x1(x());
    std::default_random_engine y1(y());
    std::uniform_int_distribution<int> to_x(0, size.first);
    std::uniform_int_distribution<int> to_y(0, size.second);

    Eat_per_step = Eat_per_step;

    std::set<coordinate> been;
    for(auto& i: robots){
        coordinate new_coor{to_x(x1), to_y(y1)};
        while(been.find(new_coor) != been.end()){
            new_coor = {to_x(x1), to_y(y1)};
        }
        been.emplace(new_coor);
        i.mCoordinates = new_coor;
    }
};
