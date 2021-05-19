#include "itembutton.h"

// Constructeur de la classe
ItemButton::ItemButton(Item *it, QWidget *parent) : QPushButton(parent)
{
    // On récupère l'item associé au bouton
    myitem = it;
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

// Fonction pour bypass le signal du QPushButton
void ItemButton::reemitClicked()
{
    emit clicked(myitem);
}
