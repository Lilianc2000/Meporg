#ifndef HEROWOLF_H
#define HEROWOLF_H

#include "wolf.h"

class HeroWolf:public Wolf{
public:
    HeroWolf(std::string name,int life,int attack,int strength, int brain);
    HeroWolf(std::string name, std::string job);
};

#endif // HEROWOLF_H
