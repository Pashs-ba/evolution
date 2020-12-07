//
// Created by pashs on 11/14/20.
//

#include "../headers/Field.h"
#include "../headers/Robot.h"

Field::Field(int Ix, int Iy, int ICountEat, int ICountPoison, int ICountWalls, int ICountRobots):
field(Iy, std::vector<Base*>(Ix))

{
    x = Ix;
    y = Iy;
    CountEat = ICountEat;
    CountWalls = ICountWalls;
    CountPoison = ICountPoison;
    CountRobots = ICountRobots;
    create_eat();
    create_poisons();
    create_walls();
    create_robots();
}
void Field::create_eat() {
    std::set<std::pair<int, int>> items;

    get_items(&items, CountEat);

    for(auto i: items){
        field[i.first][i.second] = new Eat();
    }
}

void Field::create_walls() {
    std::set<std::pair<int, int>> items;

    get_items(&items, CountWalls);

    for(auto i: items){
        field[i.first][i.second] = new Wall();
    }
}

void Field::create_poisons() {
    std::set<std::pair<int, int>> items;

    get_items(&items, CountPoison);

    for(auto i: items){
        field[i.first][i.second] = new Poison();
    }
}

void Field::create_robots() {
    std::set<std::pair<int, int>> items;
    for(auto i: items){
        std::vector<int>commands;
        for(int j = 0; j<64; j++){
            commands.push_back(rand()%11);
        }
        field[i.first][i.second] = new Robot(100, commands);
    }
}

void Field::get_items(std::set<std::pair<int, int>>* s, int count){
    while(s->size() < count){
        auto ins = std::make_pair(rand() % (x), rand() % (y));
        if(field[ins.first][ins.second] == NULL){
            s->emplace(ins);
        }

    }
}

void Field::Step() {
    for(int i = 0; i<field.size(); i++){
        for(int j = 0; j<field[i].size(); j++){
            if(j != NULL and field[i][j]->type == "Robot"){
                int response = field[i][j]->Update();
                if(response == Go){
                    int d = 0;
                    int f = 0;
                    switch (field[i][j]->GetDirection()){
                        case 1:
                            d = -1;
                        case 2:
                            f = 1;
                        case 3:
                            d = 1;
                        case 4:
                            f = -1;
                    }
                    if (y>i+d>0 and x>j+f>0 and (field[i+d][j+f] == NULL or field[i+d][j+f]->type=="Eat" or field[i+d][j+f]->type=="Poison")){
                        if(field[i+d][j+f] == NULL){
                            std::swap(field[i+d][j+f], field[i][j]);
                            return;
                        }
                        if(field[i+d][j+f]->type=="Eat"){
                            field[i+d][j+f] = NULL;
                            field[i][j] -> SetHealth(field[i][j]->GetHealth()+25);
                            std::swap(field[i+d][j+f], field[i][j]);
                        }
                        if(field[i+d][j+f]->type=="Poison"){
                            field[i+d][j+f] = NULL;
                            field[i][j] -> SetHealth(field[i][j]->GetHealth()-25);
                            std::swap(field[i+d][j+f], field[i][j]);
                        }
                    }
                }
            }
        }
    }
}