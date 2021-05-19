#ifndef ENEMYWOLF_H
#define ENEMYWOLF_H

#include "wolf.h"

class EnemyWolf:public Wolf{
public:
    EnemyWolf();
    QString getType();
};

#endif // ENEMYWOLF_H
