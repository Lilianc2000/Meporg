#include "backpack.h"

Backpack::Backpack(){
    this->setNumberItems(0);
    this->items = std::vector<Item>();

};


std::vector<Item> Backpack::getItems(){
    return this->items;
}

Item Backpack::getItem(int index){
    return this->items[index];
};

int Backpack::getNumberItems(){
    return this->number_items;
};

void Backpack::setNumberItems(int new_number_items){
    this->number_items = new_number_items;
};

void Backpack::addItem(Item new_item){
    this->items.push_back(new_item);
    this->number_items += 1;

};
void Backpack::addItems(std::vector<Item> new_items){
    this->number_items += new_items.size();
    this->items.insert(this->items.end(), new_items.begin(), new_items.end());

};
void Backpack::addItems(Backpack backpack){
    this->number_items += backpack.getNumberItems();
    this->items.insert(this->items.end(), backpack.getItems().begin(), backpack.getItems().end());
};

void Backpack::operator+(Item new_item){
    this->addItem(new_item);
};


