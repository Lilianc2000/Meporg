#include "herowerewolf.h"

HeroWerewolf::HeroWerewolf(std::string name,std::string job){
    qDebug() << "[CPP] : Creating HeroWerewolf()";

    // Read the JSON File
    QJsonDocument doc = Reader::readDataJson();


    // Setup the job
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
        throw QString("FATAL ERROR : Error generating the job in HeroWerewolf");
    }


    // Setup basic stats
    this->setAttackPoint(doc["typeHero"]["Werewolf"]["attack_point"].toInt());
    this->setLifePoint(doc["typeHero"]["Werewolf"]["life_point"].toInt());
    this->setBrainPoint(doc["typeHero"]["Werewolf"]["brain_point"].toInt());
    this->setStrengthPoint(doc["typeHero"]["Werewolf"]["strength_point"].toInt());


    // Setup the name
    this->setName(name);

    // Setup the AI
    this->setAi(false);

    // Setup the type
    this->setType(QString("Werewolf"));

    // Setup backpack
    Backpack *backpack = new Backpack();
    this->setBackpack(*backpack);
}

