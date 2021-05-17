#include "herodemon.h"

HeroDemon::HeroDemon(std::string name,int life,int attack,int strength, int brain){
    qDebug() << "[CPP] : Creating HeroDemon()";
    this->setName(name);
    this->setLifePoint(life);
    this->setAttackPoint(attack);
    this->setStrengthPoint(strength);
    this->setBrainPoint(brain);

    // Set AI
    this->setAi(false);


    // Set the type
    this->setType(QString("Demon"));

    Backpack *backpack = new Backpack();
    this->setBackpack(*backpack);
}



HeroDemon::HeroDemon(std::string name,std::string job){
    qDebug() << "[CPP] : Creating HeroDemon()";

    QJsonDocument doc = Reader::readDataJson();

    Job* hero_job;
    if (job == "Teacher"){
        Job* test_job = new Job("Teacher");
        this->setJob(*test_job);

    } else if (job == "Worker"){
        Job* test_job = new Job("Worker");
        this->setJob(*test_job);

    } else if (job == "Healer"){
        Job* test_job = new Job("Healer");
        this->setJob(*test_job);

    } else {
        hero_job = NULL;
        qDebug() << "Error dans l'argument de Game.createHero()";
    }


    this->setAttackPoint(doc["typeHero"]["Demon"]["attack_point"].toInt());
    this->setLifePoint(doc["typeHero"]["Demon"]["life_point"].toInt());
    this->setBrainPoint(doc["typeHero"]["Demon"]["brain_point"].toInt());
    this->setStrengthPoint(doc["typeHero"]["Demon"]["strength_point"].toInt());


    // Setup the name
    this->setName(name);

    // Setup the AI
    this->setAi(false);

    // Setup the type
    this->setType(QString("Demon"));

    // Setup backpack
    Backpack *backpack = new Backpack();
    this->setBackpack(*backpack);
}
