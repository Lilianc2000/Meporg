#include "item.h"

Item::Item(){
    // Reading the JSON File
     QJsonDocument doc = Reader::readDataJson();

     // Get the list of the items
     QJsonObject items = doc["items"].toObject();

     // Randomly select one of the items
     int int_name = std::rand() % items.length();
     QString key_name;
     // Find the key name of the Item of index "int_name"
     int i = 0;
     foreach(const QString& key, items.keys()) {
             if (i==int_name){
                 key_name = key;
             }
             i++;
         }

     // Setup the stats of the items
    this->setAttackPoint(doc["items"][key_name]["attack_point"].toInt());
    this->setBrainPoint(doc["items"][key_name]["brain_point"].toInt());
    this->setLifePoint(doc["items"][key_name]["life_point"].toInt());
    this->setStrengthPoint(doc["items"][key_name]["strength_point"].toInt());


    this->setName(key_name.toUtf8().constData());
}


// Getters / Setters
void Item::setName(std::string new_name){
    this->name = new_name;
};

int Item::getAttackPoint(){
    return this->attack_point;
};

void Item::setAttackPoint(int new_attack_point){
    this->attack_point = new_attack_point;
};

int Item::getBrainPoint(){
    return this->brain_point;
};

void Item::setBrainPoint(int new_brain_point){
    this->brain_point = new_brain_point;
};

int Item::getStrengthPoint(){
    return this->strength_point;
};

void Item::setStrengthPoint(int new_strength_point){
   this->strength_point = new_strength_point;
};

int Item::getLifePoint(){
    return this->life_point;
};

void Item::setLifePoint(int new_life_point){
    this->life_point = new_life_point;
};

std::string Item::getName(){
    return this->name;
}
