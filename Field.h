//
// Created by pashs on 10/27/20.
//

#ifndef EVO_FIELD_H
#define EVO_FIELD_H

#include "enums.h"
#include "Robot.h"
#include <utility>
#include <set>

class Field {
private:
    int Eat_per_step;
    int r_count;
    void generate_new_eat();
	int commandsS;
	int rHealth;
	int c_walls;
	int c_poison;
    static std::pair<int, int> find_direction(int r_dir);
	void find_coor();
	std::vector<int> make_coor(std::vector<int>& old, int f);
	void generate_walls();
	void remake_eat(std::pair<int, int> move);
	void remake_poison(std::pair<int, int> move);
	void generate_poison();
public:
    int minR;
    bool step();
    std::vector<Robot> robots;
    Field(std::pair<int, int> size, int RCount, int commands_size, int RHealth, int Eat_per_step, int minR, int walls, int poison);

    std::pair<int, int> size;
	std::vector<std::pair<int, int>> poison;
    std::vector<std::pair<int, int>> eat;
	std::vector<std::pair<int, int>> walls;
    void new_era();
};


#endif //EVO_FIELD_H
