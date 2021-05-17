#ifndef ENEMYWEREWOLF_H
#define ENEMYWEREWOLF_H

#include "werewolf.h"

class EnemyWerewolf:public Werewolf{
public:
    EnemyWerewolf();
    EnemyWerewolf(int level);
    EnemyWerewolf(QString type);
    QString getType();
};

#endif // ENEMYWEREWOLF_H
