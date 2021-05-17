#ifndef WEREWOLF_H
#define WEREWOLF_H

#include "human.h"
#include "wolf.h"

class Werewolf:public Human,public Wolf{
public:
    Werewolf();
    //void attack1(Entity entity_attacked);
    //void attack2(Entity entity_attacked);
};

#endif // WEREWOLF_H
