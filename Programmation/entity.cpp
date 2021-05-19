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


/*
 * Attacks
 *
 * The attacks always return the new life point of the attacked Entity
*/

unsigned int Entity::attack1(Entity entity_attacked){
    int total_dommages = this->getAttackPoint();

    // We use the strength to increase the damages
    int strength = this->getStrengthPoint();

    // The strength represents the pourcentage of increase of the attack
    // Its casted to float to convert to pourcentages
    int pourcentages_strength =  static_cast<float>(strength)/static_cast<float>(100);
    float dommages = static_cast<float>(total_dommages)*(1+pourcentages_strength);

    total_dommages = (int)dommages;
    int entity_attacked_life = entity_attacked.getLifePoint();

    // Return the new life point of the attacked enemy
    return entity_attacked_life - total_dommages;
};

unsigned int Entity::attack2(Entity entity_attacked){
    // We get the current life points of the enemy
    int entity_attacked_life = entity_attacked.getLifePoint();

    // Conversion to float to get 30% of the life
    float temp_dmg = static_cast<float>(entity_attacked_life) * 0.3;

    // Cast to int to return the new life of the enemy
    return entity_attacked_life - (int)temp_dmg;
};

unsigned int Entity::attack3(Entity entity_attacked){
    // We increase two fold the attack point of the attacker
    this->setAttackPoint(this->attack_point+10);

    // Return the life point of the attacked enemy
    int entity_attacked_life = entity_attacked.getLifePoint();
    return entity_attacked_life;
};

unsigned int Entity::attack4(Entity entity_attacked){
    // This attack as a 1/10 chance to one shot the enemy
    int luck = std::rand() % 10;
    if (luck==0){
        // The enemy is one shotted
        return 0;
    }
    // The enemy isn't attacked
    int entity_attacked_life = entity_attacked.getLifePoint();
    return entity_attacked_life;
};

QString Entity::getNameAttack1(){
    // Read the JSON File
    QJsonDocument doc = Reader::readDataJson();

    // Get the attack name of the first attack for each class
    if (this->getType() == QString("Demon")){
        return doc["name_attacks"]["Demon"]["name_attack_1"].toString();

    } else if (this->getType() == QString("Human")){
        return doc["name_attacks"]["Human"]["name_attack_1"].toString();

    } else if (this->getType() == QString("Wolf")){
        return doc["name_attacks"]["Wolf"]["name_attack_1"].toString();

    } else if (this->getType() == QString("Werewolf")){
        return doc["name_attacks"]["Werewolf"]["name_attack_1"].toString();
    } else {
        // Error reading the file
        //Game::generateErrorMessageBox(QString("Error_reading_name_attack_1"));
        throw QString("Error_reading_name_attack_1");
    }
};

QString Entity::getNameAttack2(){
    // Read the JSON File
    QJsonDocument doc = Reader::readDataJson();

    // Get the attack name of the second attack for each class
    if (this->getType() == QString("Demon")){
        return doc["name_attacks"]["Demon"]["name_attack_2"].toString();

    } else if (this->getType() == QString("Human")){
        return doc["name_attacks"]["Human"]["name_attack_2"].toString();

    } else if (this->getType() == QString("Wolf")){
        return doc["name_attacks"]["Wolf"]["name_attack_2"].toString();

    } else if (this->getType() == QString("Werewolf")){
        return doc["name_attacks"]["Werewolf"]["name_attack_2"].toString();
    } else {
        //Game::generateErrorMessageBox(QString("Error_reading_name_attack_1"));
        throw QString("Error_reading_name_attack_1");
    }
};

QString Entity::getNameAttack3(){
    // Read the JSON File
    QJsonDocument doc = Reader::readDataJson();

    // Get the attack name of the third attack for each class
    if (this->getType() == QString("Demon")){
        return doc["name_attacks"]["Demon"]["name_attack_3"].toString();

    } else if (this->getType() == QString("Human")){
        return doc["name_attacks"]["Human"]["name_attack_3"].toString();

    } else if (this->getType() == QString("Wolf")){
        return doc["name_attacks"]["Wolf"]["name_attack_3"].toString();

    } else if (this->getType() == QString("Werewolf")){
        return doc["name_attacks"]["Werewolf"]["name_attack_3"].toString();
    } else {
        //Game::generateErrorMessageBox(QString("Error_reading_name_attack_1"));
        throw QString("Error_reading_name_attack_1");
    }
};

QString Entity::getNameAttack4(){
    // Read the JSON File
    QJsonDocument doc = Reader::readDataJson();

    // Get the attack name of the fourth attack for each class
    if (this->getType() == QString("Demon")){
        return doc["name_attacks"]["Demon"]["name_attack_4"].toString();

    } else if (this->getType() == QString("Human")){
        return doc["name_attacks"]["Human"]["name_attack_4"].toString();

    } else if (this->getType() == QString("Wolf")){
        return doc["name_attacks"]["Wolf"]["name_attack_4"].toString();

    } else if (this->getType() == QString("Werewolf")){
        return doc["name_attacks"]["Werewolf"]["name_attack_4"].toString();
    } else {
        //Game::generateErrorMessageBox(QString("Error_reading_name_attack_1"));
        throw QString("Error_reading_name_attack_1");
    }
};


// This generate the attack for the enemies
std::tuple<QString,unsigned int> Entity::enemyAttack(Entity enemy_attacked){
    // There is 4 different attacks
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
        //Game::generateErrorMessageBox(QString("FATAL ERROR : Error generating the enemy attack "));
        throw QString("FATAL ERROR : Error generating the enemy attack ");
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


unsigned int Entity::getAttackPoint(){
    int total_attack = 0;

    // Get the attack point of the entity
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

void Entity::setAttackPoint(unsigned int new_attack_point){
    // Edge case during generation of an Entity
    // Items and jobs are not initiolized
    if (this->getIsInitialized()){
        // We discount items and the job
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
    // We discount items and the job
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

    // We get the brain from the job
    total_brain += this->job.getBonusBrainPoint();

    return total_brain;
};

void Entity::setBrainPoint(int new_brain_point){
    // We discount items and the job
    int brain_with_items = this->getBrainPoint();
    int items_bonus = brain_with_items - this->brain_point;
    this->brain_point = new_brain_point - items_bonus;};

int Entity::getStrengthPoint(){
    int total_strength = 0;
    total_strength += this->strength_point;

    // We get the strength from items
    if (this->backpack.getNumberItems() > 0){
        for (int i = 0; i<this->backpack.getNumberItems(); i++){
            total_strength += this->backpack.getItem(i).getStrengthPoint();
        }
    }

    // We get the strength from the job
    total_strength += this->job.getBonusStrengthPoint();

    return total_strength;
};

void Entity::setStrengthPoint(int new_strength_point){
    // We discount items and the job
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


// Add one item to the Backpack
void Entity::addItem(Item new_item){
    this->backpack.addItem(new_item);
};

// Add a vector of items to the backpack
void Entity::addItems(std::vector<Item> new_items){
    this->backpack.addItems(new_items);
};

// Add the items of a backpack to the backpack
void Entity::addItems(Backpack new_items){
    this->backpack.addItems(new_items);
};

// Utils
bool Entity::isDead(){
    return this->getLifePoint() <= 0;
}

// Return a QString describing the effect of tha attack 1
QString Entity::getEffectAttack1(){
    return QString("This attack does damages based on the attack and strength points of the attacker");
};

// Return a QString describing the effect of tha attack 2
QString Entity::getEffectAttack2(){
    return QString("This attack does 30% of the current life of the enemy");
};

// Return a QString describing the effect of tha attack 3
QString Entity::getEffectAttack3(){
    return QString("This attack increases the attack point of the attacker");
};

// Return a QString describing the effect of tha attack 4
QString Entity::getEffectAttack4(){
    return QString("This attack has a 1/10 chance to one shot the enemy");
};

// Overload de l'operateur +
void Entity::operator+(Item new_item){
    this->addItem(new_item);
};
