#ifndef EVO_ROBOT_H
#define EVO_ROBOT_H
#include <vector>
#include "Base.h"
#include "enums.h"


class Robot: public Base{
public:

    int Update();
    Robot(int iHealth, std::vector<int> iCommand);
private:

};

#endif //EVO_ROBOT_H
