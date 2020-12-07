//
// Created by pashs on 11/14/20.
//

#ifndef EVO_BASE_H
#define EVO_BASE_H
#include <vector>
#include <string>
#include "enums.h"

class Base {
protected:
    int health;
    std::vector<int> commands;
    int direction;
    int mIndex;
    void fix_direction();
public:
    std::string type = "NULL";
    virtual int Update() = 0;
    Base(int iHealth=NULL, std::vector<int> iCommand={NULL});


    int GetHealth();
    void SetHealth(int iHealth);

    std::vector<int> GetCommands();
    void SetCommands(std::vector<int>iCommands);

    int GetIndex();
    void SetIndex(int iIndex);
    int GetDirection();
    void SetDirection(int iDirection);
};


#endif //EVO_BASE_H
