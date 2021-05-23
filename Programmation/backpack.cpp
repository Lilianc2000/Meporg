#include "backpack.h"

Backpack::Backpack(){
    // Init
    this->setNumberItems(0);
    this->items = std::vector<Item>();

};

// Get the items in the Backpack
std::vector<Item> Backpack::getItems(){
    return this->items;
}

// Get the i-th item in the backpack
Item Backpack::getItem(int index){
    if (index < this->getNumberItems()){
        return this->items[index];
    }
    throw QString("ERRRO : Accessing an item out of range");
};

// Get the number of items in the backpack
int Backpack::getNumberItems(){
    return this->number_items;
};

void Backpack::setNumberItems(int new_number_items){
    this->number_items = new_number_items;
};

// Add one item to the backpack
void Backpack::addItem(Item new_item){
    this->items.push_back(new_item);
    this->number_items += 1;

};

// Add a vector of item to the bakcpack
void Backpack::addItems(std::vector<Item> new_items){
    this->number_items += new_items.size();
    this->items.insert(this->items.end(), new_items.begin(), new_items.end());
};

// Add a the items of a backpack to a backpack
void Backpack::addItems(Backpack backpack){
    this->number_items += backpack.getNumberItems();
    this->items.insert(this->items.end(), backpack.getItems().begin(), backpack.getItems().end());
};

// Surdefinition of the operator + between a Backpack and an Item
void Backpack::operator+(Item new_item){
    this->addItem(new_item);
};


