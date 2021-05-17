#include "infoitems.h"

InfoItems::InfoItems(QWidget *parent)
    : QDialog(parent)
{
    setup_info(this);

}

InfoItems::~InfoItems()
{
    delete ui;
}
