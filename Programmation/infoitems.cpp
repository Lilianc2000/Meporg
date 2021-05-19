#include "infoitems.h"

// Constructeur de la classe
InfoItems::InfoItems(QWidget *parent)
    : QDialog(parent)
{
    setup_info(this);

}

// Destructeur de la classe
InfoItems::~InfoItems()
{
    delete ui;
}
