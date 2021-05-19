#include "enemydemon.h"


EnemyDemon::EnemyDemon(){
    qDebug() << "[CPP] : Generating EnemyDemon()";

    this->setIsInitialized(false);

    // Settting up the type of the Demon
    this->setType(QString("Demon"));

    // Read the JSON file with the data
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
    this->setLifePoint(doc["typeEnemy"]["Demon"]["life_point"].toInt());
    this->setAttackPoint(doc["typeEnemy"]["Demon"]["attack_point"].toInt());
    this->setBrainPoint(doc["typeEnemy"]["Demon"]["brain_point"].toInt());
    this->setStrengthPoint(doc["typeEnemy"]["Demon"]["strength_point"].toInt());


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
}




