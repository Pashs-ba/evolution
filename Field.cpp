#include "Field.h"
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <iostream>

Field::Field(std::pair<int, int> size, int RCount, int commands_size, int RHealth, int eat_per_step, int min_r, int walls, int poison):
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
	c_walls = walls;
	c_poison = poison;
	find_coor();
	generate_poison();
	generate_new_eat();
	generate_walls();

}
void Field::generate_walls() {
	for (int i = 0; i < c_walls; i++) {
		std::pair<int, int> new_wall(rand() % (size.first+1), rand() % (size.second+1));
		int max = size.first * size.second;
		int now = 0;
		while (find(walls.begin(), walls.end(), new_wall) != walls.end() and now <= max) {
			new_wall = std::make_pair(rand() % (size.first+1), rand() % (size.second+1));
			now++;
		}
		if (now <= max) {
			walls.push_back(new_wall);
		}

	}
}

void Field::generate_poison() {
	for (int i = 0; i < c_poison; i++) {
		std::pair<int, int> new_poison(rand() % size.first + 1, rand() % size.second + 1);
		int max = size.first * size.second;
		int now = 0;
		while (find(poison.begin(), poison.end(), new_poison) != poison.end() and now <= max and find(eat.begin(), eat.end(), new_poison) !=eat.end()) {
			new_poison = std::make_pair(rand() % size.first+1, rand() % size.second+1);
			now++;
		}
		if (now <= max) {
			poison.push_back(new_poison);
		}

	}
}

void Field::generate_new_eat() {
	for (int i = 0; i < Eat_per_step; i++) {
		std::pair<int, int> new_eat(rand() % size.first, rand() % size.second);
		int max = size.first * size.second;
		int now = 0;
		while (find(eat.begin(), eat.end(), new_eat) != eat.end() and now <= max and find(poison.begin(), poison.end(), new_eat) != poison.end()) {
			new_eat = std::make_pair(rand() % size.first, rand() % size.second);
			now++;
		}
		if (now <= max) {
			eat.push_back(new_eat);
		}

	}


}

void Field::remake_poison(std::pair<int, int> move) {
	poison.erase(poison.begin() + distance(poison.begin(), find(poison.begin(), poison.end(), move)));

	std::pair<int, int> new_poison(rand() % size.first+1, rand() % size.second+1);
	int max = size.first * size.second;
	int now = 0;
	while (find(poison.begin(), poison.end(), new_poison) != poison.end() and find(eat.begin(), eat.end(), new_poison) != eat.end() and find(walls.begin(), walls.end(), new_poison) != walls.end()) {
		new_poison = std::make_pair(rand() % size.first+1, rand() % size.second+1);
		now++;
	}
	poison.push_back(new_poison);

}

void Field::remake_eat(std::pair<int, int> move) {
	eat.erase(eat.begin() + distance(eat.begin(), find(eat.begin(), eat.end(), move)));

	std::pair<int, int> new_eat(rand() % size.first+1, rand() % size.second+1);
	int max = size.first * size.second;
	int now = 0;
	while (find(eat.begin(), eat.end(), new_eat) != eat.end() and find(poison.begin(), poison.end(), new_eat) != poison.end() and find(walls.begin(), walls.end(), new_eat) != walls.end()) {
		new_eat = std::make_pair(rand() % size.first+1, rand() % size.second+1);
		now++;
	}
	eat.push_back(new_eat);

}



void Field::find_coor() {
	std::set<std::pair< int, int>> been;
	for (auto& i : robots) {
		std::pair<int, int> new_coor(rand() % (size.first + 1), rand() % (size.second + 1));
		while (been.find(new_coor) != been.end()) {
			new_coor = { rand() % (size.first+1), rand() % (size.second+1) };
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
		old[i] = 1+rand() % 12;
	}
		
	return old;
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
			for (auto& robot : walls) {
				if (robot == move) {
					is_Free = false;
				}
			}

            if(move.first>=0 and move.first<=size.first and move.second>=0 and move.second <= size.second and is_Free){
				for (auto& robot : eat) {
					if (robot == move) {
						i.mHealth += 35;
						remake_eat(move);
					}
				}
				for (auto& robot : poison) {
					if (robot == move) {
						i.mHealth -= 15;
						remake_poison(move);
					}
				}
                i.mCoordinates = move;
            }
        }else if(response == Eat){
            auto RDirection = find_direction(i.mDirection);
            std::pair<int, int> move = {i.mCoordinates.first + RDirection.first,
                    i.mCoordinates.second + RDirection.second};
            if(move.first>=0 and move.first<=size.first and move.second>=0 and move.second <= size.second){
				if (find(poison.begin(), poison.end(), move) != poison.end()) {
					i.mHealth -= 25;
					remake_poison(move);
				
				}
                if(find(eat.begin(), eat.end(), move) != eat.end()){
                    i.mHealth += 35;
					remake_eat(move);
//					std::cout<<"YAm"<<std::endl;
                }
            }

		}
		else if (response == Poison) {
			auto RDirection = find_direction(i.mDirection);
			std::pair<int, int> move = { i.mCoordinates.first + RDirection.first,
					i.mCoordinates.second + RDirection.second };
			if (move.first >= 0 and move.first <= size.first and move.second >= 0 and move.second <= size.second) {
				if (find(poison.begin(), poison.end(), move) != poison.end()) {
					i.mHealth += 35;
					remake_poison(move);
					//					std::cout<<"YAm"<<std::endl;
				}
			
			}
		}else if(response == Watch){
            auto RDirection = find_direction(i.mDirection);
            std::pair<int, int> move = { i.mCoordinates.first + RDirection.first,
                                         i.mCoordinates.second + RDirection.second };
            if (move.first >= 0 and move.first <= size.first and move.second >= 0 and move.second <= size.second) {
                if (find(poison.begin(), poison.end(), move) != poison.end()) {
                    i.mIndex += 1;
                }
                else if(find(eat.begin(), eat.end(), move) != eat.end()){
                    i.mIndex += 3;
                }
                else if(find(walls.begin(), walls.end(), move) != walls.end()){
                    i.mIndex += 5;
                }
                else{
                    i.mIndex += 9;
                }
                bool is_Free = true;
                for (auto & robot : robots){
                    if (robot.mCoordinates == move){
                        is_Free = false;
                    }
                }
                if(!is_Free){
                    i.mIndex += 7;
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
	walls = {};
	generate_walls();
	poison = {};
	generate_poison();
	int need_to_make = 8;
	std::vector<Robot> newR;

	for (auto& i : robots) {
		std::vector<Robot> tmp;
		for (int j = 0; j < need_to_make; j++) {
			tmp.emplace_back(commandsS, rHealth, std::pair<int, int>(-1, -1));
		}
		for (int j = 0; j < 4; j++) {
			tmp[j].commands = i.commands;
		}

        tmp[4].commands = make_coor(i.commands, 2);
		tmp[5].commands = make_coor(i.commands, 4);
		tmp[6].commands = make_coor(i.commands, 4);
		tmp[7].commands = make_coor(i.commands, 8);


        
		newR.insert(newR.end(), tmp.begin(), tmp.end());
	}
	robots = newR;
	find_coor();

}

