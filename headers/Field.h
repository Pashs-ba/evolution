//
// Created by pashs on 11/14/20.
//

#ifndef EVO_FIELD_H
#define EVO_FIELD_H
#include "Other.h"
#include "Robot.h"
#include <set>

class Field {
public:
    void step();
    std::vector<std::vector<Base*>> field;
    Field(int Ix,
          int Iy,
          int ICountEat,
          int ICountPoison,
          int ICountWalls);
private:
    int x;
    int y;
    int CountEat;
    int CountPoison;
    int CountWalls;
    void create_eat();
    void create_walls();
    void create_poisons();
    void get_items(std::set<std::pair<int, int>>* s);

};


#endif //EVO_FIELD_H
