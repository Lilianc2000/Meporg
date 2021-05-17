#include "enemywolf.h"

EnemyWolf::EnemyWolf()
{

}

EnemyWolf::EnemyWolf(QString type){
    qDebug() << "[CPP] : Generating EnemyWolf() with argument" << type;
    this->setIsInitialized(false);

    this->setType(type);
    // Default value

    QJsonDocument doc = Reader::readDataJson();

    Job* job = new Job("Teacher");
    this->setJob(*job);

    this->setLifePoint(doc["DEFAULT"]["Entity"]["default_life"].toInt());
    this->setAttackPoint(doc["DEFAULT"]["Entity"]["default_attack"].toInt());
    this->setBrainPoint(doc["DEFAULT"]["Entity"]["default_brain"].toInt());
    this->setStrengthPoint(doc["DEFAULT"]["Entity"]["default_strength"].toInt());



    // Set AI
    this->setAi(true);

    // Setup backpack
    Backpack *backpack = new Backpack();
    this->setBackpack(*backpack);

    Item *i = new Item();
    Item *i2 = new Item();
    qDebug() << "CREATING ITEMs";
    this->addItem(*i);
    this->addItem(*i2);

    // Setup name
    qDebug() << "READING NAME";
    int name = std::rand() % 49;
    QString ar =  doc["name_enemies"][name].toString();
    this->setName(ar.toUtf8().constData());

    qDebug() << this->getLifePoint();
    qDebug() << this->getAttackPoint();
    qDebug() << this->getBrainPoint();
    qDebug() << this->getStrengthPoint();

    this->setIsInitialized(true);

}


