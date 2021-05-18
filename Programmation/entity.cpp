#include "entity.h"

Entity::Entity(std::string name,int life,int attack,int strength, int brain){
    this->name = name;
    this->life_point = life;
    this->attack_point = attack;
    this->strength_point = strength;
    this->brain_point = brain;
};

Entity::Entity(std::string name){
    this->name = name;
};

Entity::Entity(){};


// Attacks
int Entity::attack1(Entity entity_attacked){
    // Return the new life point of the attacked enemy

    int total_dommages = this->getAttackPoint();

    // We use the strength to increase the damages
    int strength = this->getStrengthPoint();
    int pourcentages_strength =  static_cast<float>(strength)/static_cast<float>(100);
    float dommages = static_cast<float>(total_dommages)*(1+pourcentages_strength);

    total_dommages = (int)dommages;

    int entity_attacked_life = entity_attacked.getLifePoint();

    return entity_attacked_life - total_dommages;
};

int Entity::attack2(Entity entity_attacked){
    // We get the current lfie points of the enemy
    int entity_attacked_life = entity_attacked.getLifePoint();

    // Conversion to float to get 30% of the life
    float temp_dmg = static_cast<float>(entity_attacked_life) * 0.3;

    // Cast to int to return the new life of the enemy
    return entity_attacked_life - (int)temp_dmg;
};

int Entity::attack3(Entity entity_attacked){
    this->setAttackPoint(this->attack_point*2);

    int entity_attacked_life = entity_attacked.getLifePoint();
    return entity_attacked_life;
};

int Entity::attack4(Entity entity_attacked){
    int luck = std::rand() % 10;
    if (luck==0){
        return 0;
    }
    int entity_attacked_life = entity_attacked.getLifePoint();
    return entity_attacked_life;
};

QString Entity::getNameAttack1(){
    QJsonDocument doc = Reader::readDataJson();

    if (this->getType() == QString("Demon")){
        return doc["name_attacks"]["Demon"]["name_attack_1"].toString();

    } else if (this->getType() == QString("Human")){
        return doc["name_attacks"]["Human"]["name_attack_1"].toString();

    } else if (this->getType() == QString("Wolf")){
        return doc["name_attacks"]["Wolf"]["name_attack_1"].toString();

    } else if (this->getType() == QString("Werewolf")){
        return doc["name_attacks"]["Werewolf"]["name_attack_1"].toString();
    } else {
        return QString("Error_reading_name_attack_1");
    }
};

QString Entity::getNameAttack2(){
    QJsonDocument doc = Reader::readDataJson();

    if (this->getType() == QString("Demon")){
        return doc["name_attacks"]["Demon"]["name_attack_2"].toString();

    } else if (this->getType() == QString("Human")){
        return doc["name_attacks"]["Human"]["name_attack_2"].toString();

    } else if (this->getType() == QString("Wolf")){
        return doc["name_attacks"]["Wolf"]["name_attack_2"].toString();

    } else if (this->getType() == QString("Werewolf")){
        return doc["name_attacks"]["Werewolf"]["name_attack_2"].toString();
    } else {
        return QString("Error_reading_name_attack_1");
    }
};

QString Entity::getNameAttack3(){
    QJsonDocument doc = Reader::readDataJson();

    if (this->getType() == QString("Demon")){
        return doc["name_attacks"]["Demon"]["name_attack_3"].toString();

    } else if (this->getType() == QString("Human")){
        return doc["name_attacks"]["Human"]["name_attack_3"].toString();

    } else if (this->getType() == QString("Wolf")){
        return doc["name_attacks"]["Wolf"]["name_attack_3"].toString();

    } else if (this->getType() == QString("Werewolf")){
        return doc["name_attacks"]["Werewolf"]["name_attack_3"].toString();
    } else {
        return QString("Error_reading_name_attack_1");
    }
};

QString Entity::getNameAttack4(){
    QJsonDocument doc = Reader::readDataJson();

    if (this->getType() == QString("Demon")){
        return doc["name_attacks"]["Demon"]["name_attack_4"].toString();

    } else if (this->getType() == QString("Human")){
        return doc["name_attacks"]["Human"]["name_attack_4"].toString();

    } else if (this->getType() == QString("Wolf")){
        return doc["name_attacks"]["Wolf"]["name_attack_4"].toString();

    } else if (this->getType() == QString("Werewolf")){
        return doc["name_attacks"]["Werewolf"]["name_attack_4"].toString();
    } else {
        return QString("Error_reading_name_attack_1");
    }
};

std::tuple<QString,int> Entity::enemyAttack(Entity enemy_attacked){
    int attack = std::rand() % 3;

    int dmg;

    switch(attack) {
      case 0:
        dmg = this->attack1(enemy_attacked);
        return {this->getNameAttack1(),dmg};
        break;

      case 1:
        dmg = this->attack2(enemy_attacked);
        return {this->getNameAttack2(),dmg};
        break;

      case 2:
        dmg = this->attack3(enemy_attacked);
        return {this->getNameAttack3(),dmg};
        break;

      case 3:
        dmg = this->attack4(enemy_attacked);
        return {this->getNameAttack4(),dmg};
        break;

      default:
        qDebug() << " Error entity l.300 random ";
    }

};

//Getters/Setters
std::string Entity::getName(){
    return this->name;
};

void Entity::setName(std::string new_name){
    this->name = new_name;
};

bool Entity::getAi(){
    return this->ai;
};

void Entity::setAi(bool new_ai){
    this->ai = new_ai;
}

bool Entity::getSex(){
    return this->sex;
};

int Entity::getAttackPoint(){
    int total_attack = 0;
    total_attack += this->attack_point;

    // We get the damages from items

    if (this->backpack.getNumberItems() > 0){
        for (int i = 0; i<this->backpack.getNumberItems(); i++){
            total_attack += this->backpack.getItem(i).getAttackPoint();
        }
    }

    // We get the damages from the job
    total_attack += this->job.getBonusAttackPoint();

    return total_attack;
};

void Entity::setAttackPoint(int new_attack_point){
    if (this->getIsInitialized()){
        int attack_with_items = this->getAttackPoint();
        int items_bonus = attack_with_items - this->attack_point;
        this->attack_point = new_attack_point - items_bonus;
    } else {
        this->attack_point = new_attack_point;
    }

};

int Entity::getLifePoint(){
    int total_life = 0;
    total_life += this->life_point;

    // We get the life from items

    if (this->backpack.getNumberItems() > 0){
        for (int i = 0; i<this->backpack.getNumberItems(); i++){
            total_life += this->backpack.getItem(i).getLifePoint();
        }
    }

    // We get the life from the job
    total_life += this->job.getBonusLifePoint();

    return total_life;
};

void Entity::setLifePoint(int new_life_point){
    int life_with_items = this->getLifePoint();
    int items_bonus = life_with_items - this->life_point;
    this->life_point = new_life_point - items_bonus;
};

int Entity::getBrainPoint(){
    int total_brain = 0;
    total_brain += this->brain_point;

    // We get the brain from items

    if (this->backpack.getNumberItems() > 0){
        for (int i = 0; i<this->backpack.getNumberItems(); i++){
            total_brain += this->backpack.getItem(i).getBrainPoint();
        }
    }



    // We get the life from the job
    total_brain += this->job.getBonusBrainPoint();

    return total_brain;
};

void Entity::setBrainPoint(int new_brain_point){
    int brain_with_items = this->getBrainPoint();
    int items_bonus = brain_with_items - this->brain_point;
    this->brain_point = new_brain_point - items_bonus;};

int Entity::getStrengthPoint(){
    int total_strength = 0;
    total_strength += this->strength_point;

    // We get the life from items

    if (this->backpack.getNumberItems() > 0){
        for (int i = 0; i<this->backpack.getNumberItems(); i++){
            total_strength += this->backpack.getItem(i).getStrengthPoint();
        }
    }



    // We get the life from the job
    total_strength += this->job.getBonusStrengthPoint();

    return total_strength;
};

void Entity::setStrengthPoint(int new_strength_point){
    int strength_with_items = this->getStrengthPoint();
    int items_bonus = strength_with_items - this->strength_point;
    this->strength_point = new_strength_point - items_bonus;};

Job Entity::getJob(){
    return this->job;
}

void Entity::setJob(Job job){
    this->job = job;
}

QString Entity::getType(){
    return this->type;
}

void Entity::setType(QString type){
    this->type = type;
}

bool Entity::getIsInitialized(){
    return this->isInitialized;
}

void Entity::setIsInitialized(bool new_init){
    this->isInitialized = new_init;
}


// Items
Backpack Entity::getItems(){
    return this->backpack;
};

void Entity::setBackpack(Backpack new_backpack){
    this->backpack = new_backpack;
};


void Entity::addItem(Item new_item){
    this->backpack.addItem(new_item);
};

void Entity::addItems(std::vector<Item> new_items){
    this->backpack.addItems(new_items);
};

void Entity::addItems(Backpack new_items){
    this->backpack.addItems(new_items);
};

// Utils
bool Entity::isDead(){
    return this->getLifePoint() <= 0;
}

void Entity::setDefaultLife(){
    this->setLifePoint(10);
}


QString Entity::getEffectAttack1(){
    return QString("This attack does damages based on the attack and strength points of the attacker");
};

QString Entity::getEffectAttack2(){
    return QString("This attack does 30% of the current life of the enemy");
};

QString Entity::getEffectAttack3(){
    return QString("This attack increases the attack point of the attacker");
};

QString Entity::getEffectAttack4(){
    return QString("This attack has a 1/10 chance to one shot the enemy");
};

// Overload de l'operateur +
void Entity::operator+(Item new_item){
    this->addItem(new_item);
};
