#include "enemywerewolf.h"

EnemyWerewolf::EnemyWerewolf(){
    qDebug() << "[CPP] : Generating EnemyWerewolf()";

    this->setIsInitialized(false);

    this->setType(QString("Werewolf"));

    QJsonDocument doc = Reader::readDataJson();

    // Setup the job
    int jobint = std::rand() % 2;
    Job* job;
    switch (jobint) {
        case 0:
            job = new Job("Teacher");
            break;
        case 1:
            job = new Job("Worker");
            break;
        case 2:
            job = new Job("Healer");
            break;
    }
    this->setJob(*job);

    // Setup the base stats of the Demon
    this->setLifePoint(doc["typeEnemy"]["Human"]["life_point"].toInt());
    this->setAttackPoint(doc["typeEnemy"]["Human"]["attack_point"].toInt());
    this->setBrainPoint(doc["typeEnemy"]["Human"]["brain_point"].toInt());
    this->setStrengthPoint(doc["typeEnemy"]["Human"]["strength_point"].toInt());

    // Set AI
    this->setAi(true);

    // Setup backpack
    Backpack *backpack = new Backpack();
    this->setBackpack(*backpack);

    // Create base Item from the EnemyDemon
    Item *i = new Item();
    Item *i2 = new Item();
    this->addItem(*i);
    this->addItem(*i2);


    // Setup name
    int name = std::rand() % 49;
    QString ar =  doc["name_enemies"][name].toString();
    this->setName(ar.toUtf8().constData());

    this->setIsInitialized(true);
};
