//
// Created by pashs on 11/14/20.
//

#include "../headers/Base.h"

Base::Base(int iHealth, std::vector<int> iCommand):
commands(iCommand)
{
    direction = 0;
    health=iHealth;
    mIndex = 0;
}
void Base::fix_direction() {
    if(direction>4){
        direction-=4;

    }if(direction<0){
        direction+=4;
    }
}


int Base::GetIndex() {return mIndex;}
void Base::SetIndex(int iIndex){mIndex=iIndex;}

int Base::GetHealth() {return health;}
void Base::SetHealth(int iHealth){health=iHealth;}

std::vector<int> Base::GetCommands() {return commands;}
void Base::SetCommands(std::vector<int> iCommands) {commands == iCommands;}