#ifndef ENEMYDEMON_H
#define ENEMYDEMON_H

#include "demon.h"


class EnemyDemon:public Demon{
public:
    EnemyDemon();
    EnemyDemon(int level);
    EnemyDemon(QString type);
    QString getType();
};

#endif // ENEMYDEMON_H
