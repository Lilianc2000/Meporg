#include "mainwindow.h"
#include "aboutwindow.h"
#include <QApplication>

// Main de notre programme
int main(int argc, char *argv[])
{
    // On déclare une nouvellee QApplication
    QApplication a(argc, argv);

    // On créer la fenêtre à partir de MainWindow
    MainWindow w;
    w.show();

    // On lance le programme (syntaxe propre à QT)
    return a.exec();
}
