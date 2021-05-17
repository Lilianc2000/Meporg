#include "itembutton.h"

ItemButton::ItemButton(Item *it, QWidget *parent) : QPushButton(parent)
{
    myitem = it;
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}


void ItemButton::reemitClicked()
{
    emit clicked(myitem);
}
