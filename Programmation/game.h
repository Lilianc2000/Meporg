#ifndef GAME_H
#define GAME_H

#include <string>
#include <list>
#include <vector>
#include <QDebug>

#include <QMessageBox>


#include "reader.h"

#include "herodemon.h"
#include "herohuman.h"
#include "herowolf.h"
#include "herowerewolf.h"

#include "enemydemon.h"
#include "enemyhuman.h"
#include "enemywolf.h"
#include "enemywerewolf.h"

class Game
{
public:
    Game();
    static Entity* createHero(std::string name,std::string class_type,std::string job);
    static std::vector<Entity*> createEnemies(int number_enemies);

    static QJsonDocument readDataJson();

    static int readHighScore();
    static void setHighScore(int new_highscore);
    static void resetHighScore();

    static void generateErrorMessageBox(QString error);

};

#endif // GAME_H
