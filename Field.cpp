#include "Field.h"
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <iostream>

Field::Field(std::pair<int, int> size, int RCount, int commands_size, int RHealth, int eat_per_step, int min_r):
    size(size)

{
    for(int i = 0; i<RCount; ++i){
        robots.emplace_back(commands_size, RHealth, std::pair<int, int>(-1, -1));
    }
    Eat_per_step = eat_per_step;
    minR = min_r;
    r_count = RCount;
	rHealth = RHealth;
	commandsS = commands_size;
	find_coor();
	generate_new_eat();

}

void Field::find_coor() {
	std::set<std::pair< int, int>> been;
	for (auto& i : robots) {
		std::pair<int, int> new_coor(rand() % size.first, rand() % size.second);
		while (been.find(new_coor) != been.end()) {
			new_coor = { rand() % size.first, rand() % size.second };
		}
		been.emplace(new_coor);
		i.mCoordinates = new_coor;
	}
}
std::vector<int> Field::make_coor(std::vector<int>& old, int f)
{
	std::set<int> s;
	while (s.size() != f) {
		s.emplace(rand() % 64);
	}
	for (auto i : s) {
		old[i] = rand() % 10;
	}
		
	return old;
}
void Field::generate_new_eat() {
    for(int i = 0; i<Eat_per_step; i++){
        std::pair<int, int> new_eat(rand()%size.first, rand()%size.second);
        int max = size.first *size.second;
        int now = 0;
        while(find(eat.begin(), eat.end(), new_eat) != eat.end() and now<=max){
            new_eat = std::make_pair(rand()%size.first, rand()%size.second);
            now++;
        }
        if(now<=max){
            eat.push_back(new_eat);
        }

    }


}

std::pair<int, int> Field::find_direction(int r_dir) {
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
bool Field::step(){
    
    for(auto& i: robots){
        int response = i.update();
        if (response == Go){
            auto RDirection = find_direction(i.mDirection);
            std::pair<int, int> move = {i.mCoordinates.first + RDirection.first,
                    i.mCoordinates.second + RDirection.second};
            bool is_Free = true;
            for (auto & robot : robots){
                if (robot.mCoordinates == move){
                    is_Free = false;
                }
            }

            if(move.first>=0 and move.first<=size.first and move.second>=0 and move.second <= size.second and is_Free){
                i.mCoordinates = move;
            }
        }else if(response == Eat){
            auto RDirection = find_direction(i.mDirection);
            std::pair<int, int> move = {i.mCoordinates.first + RDirection.first,
                    i.mCoordinates.second + RDirection.second};
            if(move.first>=0 and move.first<=size.first and move.second>=0 and move.second <= size.second){
                if(find(eat.begin(), eat.end(), move) != eat.end()){
                    i.mHealth += 2;
                    eat.erase(eat.begin()+distance(eat.begin(), find(eat.begin(), eat.end(), move)));

					std::pair<int, int> new_eat(rand() % size.first, rand() % size.second);
					int max = size.first * size.second;
					int now = 0;
					while (find(eat.begin(), eat.end(), new_eat) != eat.end()) {
						new_eat = std::make_pair(rand() % size.first, rand() % size.second);
						now++;
					}
					eat.push_back(new_eat);
//					std::cout<<"YAm"<<std::endl;
                }
            }

        }
        i.mHealth--;
        if(robots.size() == 8){
            new_era();
            return true;
        }
        if (i.mHealth<=0){
            for (int j = 0; j<robots.size(); j++){
                if (robots[j].mCoordinates == i.mCoordinates){
                    robots.erase(robots.begin() + j);
                }
            }

        }
    }
    return false;
}


void Field::new_era() {
    eat = {};
	generate_new_eat();
	int need_to_make = r_count / 8;
	std::vector<Robot> newR;

	for (auto& i : robots) {
		std::vector<Robot> tmp;
		for (int j = 0; j < need_to_make; j++) {
			tmp.emplace_back(commandsS, rHealth, std::pair<int, int>(-1, -1));
		}
		for (int j = 0; j < 5; j++) {
			tmp[j].commands = i.commands;
		}
		tmp[2].commands = make_coor(i.commands, 2);
        tmp[3].commands = make_coor(i.commands, 8);
        tmp[4].commands = make_coor(i.commands, 16);
		newR.insert(newR.end(), tmp.begin(), tmp.end());
	}
	robots = newR;
	find_coor();

}

