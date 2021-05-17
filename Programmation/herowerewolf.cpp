#include "herowerewolf.h"


HeroWerewolf::HeroWerewolf(std::string name,int life,int attack,int strength, int brain){
    this->setName(name);
    this->setLifePoint(life);
    this->setAttackPoint(attack);
    this->setStrengthPoint(strength);
    this->setBrainPoint(brain);

    // Set AI
    this->setAi(false);

    // Set the type
    this->setType(QString("Werewolf"));

    Backpack *backpack = new Backpack();
    this->setBackpack(*backpack);
}

HeroWerewolf::HeroWerewolf(std::string name,std::string job){
    qDebug() << "[CPP] : Creating HeroWerewolf()";

    // Setup attack,life,brain,strength
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
