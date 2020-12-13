//
// Created by pashs on 11/14/20.
//

#ifndef EVO_FIELD_H
#define EVO_FIELD_H
#include "Other.h"
#include "Robot.h"
#include <set>
#include <iostream>

class Field {
public:
    void Step();
    std::vector<std::vector<Base*>> field;
    Field(int Ix,
          int Iy,
          int ICountEat,
          int ICountPoison,
          int ICountWalls,
          int ICountRobots
          );
private:
    int x;
    int y;
    int CountEat;
    int CountPoison;
    int CountWalls;
    int CountRobots;
    int new_count;
    void create_eat();
    void create_walls();
    void create_poisons();
    void get_items(std::set<std::pair<int, int>>* s, int count);
    void create_robots();
    void randomize_commands(std::vector<int>& commands);
    void create_new_eat();
    void create_new_poison();
    void create_new_robot(int i, int j);


};


#endif //EVO_FIELD_H
