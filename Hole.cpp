//
// Created by pashs on 10/27/20.
//

#include "Hole.h"
#include <utility>
#include <set>
#include <algorithm>

Hole::Hole(std::pair<int, int> size, int RCount,int commands_size, int RHealth, int eat_per_step, int min_r):
    size(size),
    robots(RCount, Robot(commands_size, RHealth, std::pair<int, int>(-1, -1)))
{
    Eat_per_step = eat_per_step;
    minR = min_r;
    std::set<std::pair< int, int>> been;
    for(auto& i: robots){
        std::pair<int, int> new_coor(rand()%size.first+1, rand()%size.second+1);
        while(been.find(new_coor)!= been.end()){
            new_coor = {rand()%size.first+1, rand()%size.second+1};
        }
        been.emplace(new_coor);
        i.mCoordinates = new_coor;
    }
}
void Hole::main(){
    while(robots.size()>minR){
       step();
    }
}
void Hole::generate_new_eat() {
    for(int i = 0; i<Eat_per_step; i++){
        std::pair<int, int> new_eat(rand()%size.first+1, rand()%size.second+1);
        int max = size.first *size.second;
        int now = 0;
        while(eat.find(new_eat)!= eat.end() and now<max){
            new_eat = {rand()%size.first+1, rand()%size.second+1};\
            now++;
        }
        eat.emplace(new_eat);
    }


}

std::pair<int, int> Hole::find_direction(int r_dir) {
    if (r_dir == 1){
        return {0, -1};
    }if (r_dir == 2){
        return {1, 0};
    }if (r_dir == 3){
        return {0, 1};
    }if (r_dir == 4){
        return {-1, 0};
    }
}
void Hole::step(){
    generate_new_eat();
    for(auto& i: robots){
        int response = i.update();
        if (response == Go){
            auto RDirection = find_direction(i.mDirection);
            std::pair<int, int> move = {i.mCoordinates.first += RDirection.first,
                    i.mCoordinates.second += RDirection.second};
            bool is_Free = true;
            for (auto & robot : robots){
                if (robot.mCoordinates == i.mCoordinates){
                    is_Free = false;
                }
            }

            if(move.first>=0 and move.first<=size.first and move.second>=0 and move.second <= size.second and is_Free){
                i.mCoordinates = move;
            }
        }else if(response == Eat){
            auto RDirection = find_direction(i.mDirection);
            std::pair<int, int> move = {i.mCoordinates.first += RDirection.first,
                    i.mCoordinates.second += RDirection.second};
            if(move.first>=0 and move.first<=size.first and move.second>=0 and move.second <= size.second){
                if(eat.find(move) != eat.end()){
                    i.mHealth += 2;
                    eat.erase(move);
                }
            }

        }
        i.mHealth--;
        if (i.mHealth<=0){
            for (int j = 0; j<robots.size(); j++){
                if (robots[j].mCoordinates == i.mCoordinates){
                    robots.erase(robots.begin() + j);
                }
            }

        }
    }
}