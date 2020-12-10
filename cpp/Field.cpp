//
// Created by pashs on 11/14/20.
//

#include "../headers/Field.h"

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
                int move_y = 0;
                int move_x = 0;
                int mass = 25;
                switch (field[i][j]->GetDirection()){
                    case 1:
                        move_y = -1;
                    case 2:
                        move_x = 1;
                    case 3:
                        move_y = 1;
                    case 4:
                        move_x = -1;
                }
                if(response == Go){
                    if (y > i + move_y > 0 and x > j + move_x > 0 and (field[i + move_y][j + move_x] == NULL or field[i + move_y][j + move_x]->type == "Eat" or field[i + move_y][j + move_x]->type == "Poison")){
                        if(field[i + move_y][j + move_x] == NULL){
                            std::swap(field[i + move_y][j + move_x], field[i][j]);
                            return;
                        }
                        if(field[i + move_y][j + move_x]->type == "Eat"){
                            field[i + move_y][j + move_x] = NULL;
                            field[i][j] -> SetHealth(field[i][j]->GetHealth()+mass);
                            std::swap(field[i + move_y][j + move_x], field[i][j]);
                        }
                        if(field[i + move_y][j + move_x]->type == "Poison"){
                            field[i + move_y][j + move_x] = NULL;
                            field[i][j] -> SetHealth(field[i][j]->GetHealth()-mass);
                            std::swap(field[i + move_y][j + move_x], field[i][j]);
                        }
                    }
                }
                if (y > i + move_y > 0 and x > j + move_x > 0 and field[i + move_y][j + move_x] != NULL) {
                    if (response == Eating) {
                        if (field[i + move_y][j + move_x]->type == "Eat") {
                            field[i + move_y][j + move_x] = NULL;
                            field[i][j]->SetHealth(field[i][j]->GetHealth() + mass);
                        }
                    }
                    if (response == Poising) {
                        if (field[i + move_y][j + move_x]->type == "Poison") {
                            field[i + move_y][j + move_x] = NULL;
                            field[i][j]->SetHealth(field[i][j]->GetHealth() + mass-10);
                        }
                    }
                }
                if(response == Watch){
                    if (y > i + move_y > 0 and x > j + move_x > 0){
                        int move = 0;
                        if(field[i + move_y][j + move_x] != NULL){
                            move = 1;
                        }else{
                            if(field[i + move_y][j + move_x]->type == "Eat"){
                                move = 2;
                            }
                            if(field[i + move_y][j + move_x]->type == "Poison"){
                                move = 2;
                            }
                            if(field[i + move_y][j + move_x]->type == "Wall"){
                                move = 3;
                            }
                        }
                        field[i][j] -> SetDirection(field[i][j] ->GetDirection()+move);

                    }
                }
                if(field[i][j] ->GetHealth() > 100){
                    field[i][j]->SetHealth(field[i][j] ->GetHealth()-100);
                    std::vector<int> to_y = {1, 1, 1, 0, -1, -1, -1, 0};
                    std::vector<int> to_x = {-1, 0, 1, 1, 1, 0, -1, -1};
                    for(int k = 0; k<8; k++){
                        if(y > i + to_y[k] > 0 and x > j + to_x[k] > 0 and field[i+to_y[k]][j+to_x[k]] == NULL){
                            std::vector<int> commands = field[i][j] -> GetCommands();
                            randomize_commands(commands);
                            field[i+to_y[k]][j+to_x[k]] = new Robot(100, commands);
                            break;
                        }
                    }
                }
                if(field[i][j] ->GetHealth() <= 0){
                    field[i][j] = NULL;
                }
                field[i][j] -> SetHealth(field[i][j] -> GetHealth());
            }
        }
    }
}

void Field::randomize_commands(std::vector<int>& command){
    std::set<int> coor;
    for(int i = 0; i<8; i++){
        coor.insert(rand()%65);
    }
    for(auto i: coor){
        command[i] = rand()%11;
    }
}