#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

// On inclue les librairies nécessaires à notre boutton personnalisé
#include <QPushButton>
#include "item.h"

// On défini notre classe de bouton personnalisé
class ItemButton: public QPushButton
{
    Q_OBJECT
    
public:
    ItemButton(Item *it, QWidget *parent);
    
// Cette classe dispose d'un signal clicked qui surdéfini celui du QPushButton traditionnel
// Grâce à ca, on peut faire passer l'item associé au bouton à la fonction en charge d'ajouter l'item à l'inventaire du héro (voir mainwindow.cpp)
Q_SIGNAL void clicked(Item *);

private:
Q_SLOT void reemitClicked();
    
private:
    Item *myitem;
};
#endif // ITEMBUTTON_H
