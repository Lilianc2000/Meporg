#ifndef HERODEMON_H
#define HERODEMON_H

#include "demon.h"

#include <qDebug>

class HeroDemon:public Demon{
public:
    HeroDemon(std::string name,int life,int attack,int strength, int brain);
    HeroDemon(std::string name, std::string job);
};

#endif // HERODEMON_H
