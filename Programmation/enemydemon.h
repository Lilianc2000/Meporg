#ifndef ENEMYDEMON_H
#define ENEMYDEMON_H

#include "demon.h"


class EnemyDemon:public Demon{
public:
    EnemyDemon();
    QString getType();
};

#endif // ENEMYDEMON_H
