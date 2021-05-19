#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <list>
#include <tuple>

#include "job.h"

#include "backpack.h"

class Entity
{
public:
    Entity(std::string name,int life,int attack,int strength, int brain);
    Entity(std::string name);
    Entity();
    unsigned int attack1(Entity entity_attacked);
    unsigned int attack2(Entity entity_attacked);
    unsigned int attack3(Entity entity_attacked);
    unsigned int attack4(Entity entity_attacked);


    //Getters/Setters
    std::string getName();
    void setName(std::string new_name);

    bool getAi();
    void setAi(bool ai);

    bool getSex();

    unsigned int getAttackPoint();
    void setAttackPoint(unsigned int new_attack_point);

    int getLifePoint();
    void setLifePoint(int new_life_point);

    int getBrainPoint();
    void setBrainPoint(int new_brain_point);

    int getStrengthPoint();
    void setStrengthPoint(int new_strength_point);

    Backpack getItems();
    void setBackpack(Backpack new_backpack);
    void addItem(Item new_item);
    void addItems(std::vector<Item> new_items);
    void addItems(Backpack new_items);


    Job getJob();
    void setJob(Job job);

    QString getType();
    void setType(QString new_name);

    bool getIsInitialized();
    void setIsInitialized(bool new_init);

    // Function
    bool isDead();

    QString getNameAttack1();
    QString getNameAttack2();
    QString getNameAttack3();
    QString getNameAttack4();

    std::tuple<QString,unsigned int> enemyAttack(Entity enemy_attacked);



    void operator+(Item new_item);

    QString getEffectAttack1();
    QString getEffectAttack2();
    QString getEffectAttack3();
    QString getEffectAttack4();

    virtual ~Entity() = default;


private:
    std::string name;
    bool ai;
    int attack_point;
    int life_point;
    int brain_point;
    int strength_point;
    bool sex;
    Backpack backpack;
    Job job;

    QString name_attack_1;
    QString name_attack_2;
    QString name_attack_3;
    QString name_attack_4;

    QString type;

    bool isInitialized;

};

#endif // ENTITY_H
