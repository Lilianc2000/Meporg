#include "level.h"

Level::Level(){
};

int Level::getNumberEnemies(){
    return this->number_enemies;
};

int Level::getEnvironment(){
    return this->environment;
};

int Level::getValue(){
    return this->value;
};
