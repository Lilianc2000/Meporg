#include "aboutwindow.h"

// Constructeur de la classe
AboutWindow::AboutWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    setFixedSize(320, 240);

}

// Destructeur de la classe
AboutWindow::~AboutWindow()
{
    delete ui;
}
