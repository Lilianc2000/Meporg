#ifndef LEVEL_H
#define LEVEL_H


class Level
{
public:
    Level();
    int getNumberEnemies();
    int getEnvironment();
    int getValue();

private:
    int number_enemies;
    int environment;
    int value;
};

#endif // LEVEL_H
