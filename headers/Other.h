//
// Created by pashs on 11/14/20.
//

#ifndef EVO_OTHER_H
#define EVO_OTHER_H
#include "Base.h"
class Wall: public Base{
public:
    Wall(){
        type="Wall";
    };
    int Update(){return 0;};
};

class Eat: public Base{
public:
    Eat(){
        type="Eat";
    };
    int Update(){return 0;};
};

class Poison: public Base{
public:
    Poison(){
        type="Poison";
    };
    int Update(){return 0;};
};
#endif //EVO_OTHER_H
