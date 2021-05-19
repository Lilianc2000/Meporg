#include "herodemon.h"

HeroDemon::HeroDemon(std::string name,std::string job){
    qDebug() << "[CPP] : Creating HeroDemon()";

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
        //Game::generateErrorMessageBox(QString("FATAL ERROR : Error generating the job in HeroDemon"));
        throw QString("FATAL ERROR : Error generating the job in HeroDemon");
    }


    // Setup basic stats
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
