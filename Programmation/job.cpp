#include "job.h"
#include <iostream>



Job::Job(){}

Job::Job(std::string name_job){
    QString str = QString::fromUtf8(name_job.c_str());
    qDebug() << QString("[CPP] : Creating Job with argument : ") + str;



    QJsonDocument doc = Reader::readDataJson();

    if (name_job == "Teacher"){
        qDebug() << " CREATING JOB WITH TEACHER";
        this->setBonusAttackPoint(doc["job"]["Teacher"]["bonus_attack_point"].toInt());
        this->setBonusBrainPoint(doc["job"]["Teacher"]["bonus_brain_point"].toInt());
        this->setBonusStrengthPoint(doc["job"]["Teacher"]["bonus_strength_point"].toInt());
        this->setBonusLifePoint(doc["job"]["Teacher"]["bonus_life_point"].toInt());


    } else if (name_job == "Worker"){
        this->setBonusAttackPoint(doc["job"]["Worker"]["bonus_attack_point"].toInt());
        this->setBonusBrainPoint(doc["job"]["Worker"]["bonus_brain_point"].toInt());
        this->setBonusStrengthPoint(doc["job"]["Worker"]["bonus_strength_point"].toInt());
        this->setBonusLifePoint(doc["job"]["Worker"]["bonus_life_point"].toInt());

    } else if (name_job == "Healer"){
        this->setBonusAttackPoint(doc["job"]["Healer"]["bonus_attack_point"].toInt());
        this->setBonusBrainPoint(doc["job"]["Healer"]["bonus_brain_point"].toInt());
        this->setBonusStrengthPoint(doc["job"]["Healer"]["bonus_strength_point"].toInt());
        this->setBonusLifePoint(doc["job"]["Healer"]["bonus_life_point"].toInt());
    } else {
        qDebug() << "ERRROR READING DATA ABOUT JOBS";
    }

    qDebug() << this->getBonusAttackPoint();
    qDebug() << this->getBonusLifePoint();
    qDebug() << this->getBonusStrengthPoint();
    qDebug() << this->getBonusBrainPoint();


};


int Job::getBonusBrainPoint(){
    return this->bonus_brain_point;
};

void Job::setBonusBrainPoint(int new_bonus_brain_point){
    this->bonus_brain_point = new_bonus_brain_point;
};

int Job::getBonusStrengthPoint(){
    return this->bonus_strength_point;
};

void Job::setBonusStrengthPoint(int new_bonus_strength_point){
    this->bonus_strength_point = new_bonus_strength_point;
};

int Job::getBonusLifePoint(){
    return this->bonus_life_point;
};

void Job::setBonusLifePoint(int new_bonus_life_point){
    this->bonus_life_point = new_bonus_life_point;
};

int Job::getBonusAttackPoint(){
    return this->bonus_attack_point;
};

void Job::setBonusAttackPoint(int new_bonus_attack_point){
    this->bonus_attack_point = new_bonus_attack_point;
};
