#ifndef JOB_H
#define JOB_H

#include "reader.h"

#include <string>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QJsonDocument>




class Job{
public:
    Job();
    Job(std::string name_job);
    Job(int bonus_brain_point,int bonus_strength_point,int bonus_attack_point,int bonus_life_point);
    int getBonusBrainPoint();
    void setBonusBrainPoint(int new_bonus_brain_point);

    int getBonusStrengthPoint();
    void setBonusStrengthPoint(int new_bonus_strength_point);

    int getBonusLifePoint();
    void setBonusLifePoint(int new_bonus_life_point);

    int getBonusAttackPoint();
    void setBonusAttackPoint(int new_bonus_attack_point);

    ~Job() = default;


private:
    int bonus_brain_point;
    int bonus_strength_point;
    int bonus_life_point;
    int bonus_attack_point;
};

#endif // JOB_H
