//
// Created by pashs on 11/14/20.
//

#include "../headers/Field.h"

Field::Field(int Ix, int Iy, int ICountEat, int ICountPoison, int ICountWalls):
field(Iy, std::vector<Base*>(Ix))

{
//    create_eat();
//    create_poisons();
//    create_walls();
    x = Ix;
    y = Iy;
    CountEat = ICountEat;
    CountWalls = ICountWalls;
    CountPoison = ICountPoison;
    create_eat();
    create_poisons();
    create_walls();
}
void Field::create_eat() {
    std::set<std::pair<int, int>> items;

    while(items.size() < CountEat){
        auto ins = std::make_pair(rand() % (x), rand() % (y));
        if(field[ins.first][ins.second] == NULL){
            items.emplace(ins);
        }

    }
    for(auto i: items){
        field[i.first][i.second] = new Eat();
    }
}

void Field::create_walls() {
    std::set<std::pair<int, int>> items;


    while(items.size() < CountWalls){
        auto ins = std::make_pair(rand() % (x), rand() % (y));
        if(field[ins.first][ins.second] == NULL){
            items.emplace(ins);
        }

    }
    for(auto i: items){
        field[i.first][i.second] = new Wall();
    }
}

void Field::create_poisons() {
    std::set<std::pair<int, int>> items;


    while(items.size() < CountPoison){
        auto ins = std::make_pair(rand() % (x), rand() % (y));
        if(field[ins.first][ins.second] == NULL){
            items.emplace(ins);
        }

    }
    for(auto i: items){
        field[i.first][i.second] = new Poison();
    }
}

void Field::get_items(std::set<std::pair<int, int>>* s){
    for(int i = 0; i<field.size(); i++){
        for(int j = 0; j<field[i].size(); j++){
            if(field[i][j] != NULL){
                s->emplace(std::make_pair(i, j));
            }

        }
    }
}
