#ifndef BACKPACK_H
#define BACKPACK_H

#include "item.h"


#include <vector>


class Backpack
{
public:
    Backpack();
    Backpack getBackpack();
    std::vector<Item> getItems();
    Item getItem(int index);

    int getNumberItems();
    void setNumberItems(int new_number_items);

    void addItem(Item new_item);
    void addItems(std::vector<Item> new_items);
    void addItems(Backpack backpack);

    void operator+(Item new_item);

private:
    std::vector<Item> items;
    int number_items;
};

#endif // BACKPACK_H
