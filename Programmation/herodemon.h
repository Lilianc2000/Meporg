#ifndef HERODEMON_H
#define HERODEMON_H

#include "demon.h"

#include <QDebug>

class HeroDemon:public Demon{
public:
    HeroDemon(std::string name, std::string job);
};

#endif // HERODEMON_H
