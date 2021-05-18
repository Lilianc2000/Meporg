#include "game.h"

Game::Game(){
}

Entity* Game::createHero(std::string name,std::string class_type,std::string job){
    // Le hero qui sera renvoyé
    Entity* h;

    // On crée la classe Hero avec la bonne classe
    if (class_type == "Demon"){
        h = new HeroDemon(name,job);
        //h = new HeroDemon(name,10,10,10,10);
    } else if (class_type == "Human"){
        h = new HeroHuman(name,job);
        //h = new HeroHuman(name,10,10,10,10);
    } else if (class_type == "Wolf"){
        h = new HeroWolf(name,job);
        //h = new HeroWolf(name,10,10,10,10);
    } else if (class_type == "Werewolf"){
        h = new HeroWerewolf(name,job);
        //h = new HeroWerewolf(name,10,10,10,10);
    } else {
        qDebug() << "Error  : mauvaise entrée dans la fonction Game.createHero";
        h = NULL;
    }

    /*
    // We setup the job
    Job* hero_job;
    if (job == "Teacher"){
        Job* test_job = new Job("Teacher");
        h->setJob(*test_job);

    } else if (job == "Worker"){
        Job* test_job = new Job("Worker");
        h->setJob(*test_job);

    } else if (job == "Healer"){
        Job* test_job = new Job("Healer");
        h->setJob(*test_job);

    } else {
        hero_job = NULL;
        qDebug() << "Error dans l'argument de Game.createHero()";
    }*/

    return h;

};

std::vector<Entity*> Game::createEnemies(int number_enemies){
    std::vector<Entity*> enemies;

    for (int i = 0; i < number_enemies; i++){
        int class_enemy = std::rand() % 4;
        if (class_enemy == 1){
            Entity* enemy = new EnemyDemon(QString("Demon"));
            enemies.push_back(enemy);

        } else if (class_enemy == 2) {
            Entity* enemy = new EnemyHuman(QString("Human"));
            enemies.push_back(enemy);

        } else if (class_enemy == 3) {
            Entity* enemy = new EnemyWolf(QString("Wolf"));
            enemies.push_back(enemy);

        } else if (class_enemy == 4) {
            Entity* enemy = new EnemyWerewolf(QString("Werewolf"));
            enemies.push_back(enemy);

        }

    }

    return enemies;

};


int Game::readHighScore(){
    QJsonDocument doc = Reader::readDataJson();
    return doc["highscore"].toInt();
};


void Game::setHighScore(int new_highscore){
    QJsonDocument doc = Reader::readDataJson();
    QJsonObject root(doc.object());
    root["highscore"] = new_highscore;

    QString path = qApp->applicationDirPath() + "/ressources/data.json";
    QFile file(path);
    doc.setObject(root);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
};
