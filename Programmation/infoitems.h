#ifndef INFOITEMS_H
#define INFOITEMS_H

// On inclue les librairies nécessaires à la fenêtre "A Propos"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QtWidgets/QMainWindow>
#include <QDesktopServices>
#include "reader.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

// On défini le namespace pour QT
QT_BEGIN_NAMESPACE
namespace Ui {
    class InfoItems;
} // namespace Ui

QT_END_NAMESPACE

// On initialise la classe InfoItems

class InfoItems : public QDialog
{

public:

    QWidget *centralwidget;
    QGridLayout *gridLayout;

    QPushButton *close_button;

    QLabel *image;
    QLabel *text;

    InfoItems(QWidget *parent = nullptr);
    ~InfoItems();

    void setup_info(QDialog *Dialog){

        QJsonDocument doc = Reader::readDataJson();
        QJsonObject items = doc["items"].toObject();

        Dialog->setObjectName("ItemsInfo");

        // On initialise le coeur de l'accueil avec un widget principal, un label pour le background, deux labels pour les messages d'accueil
        centralwidget = new QWidget(Dialog);
        centralwidget->setObjectName("centralwidget");

        gridLayout = new QGridLayout(centralwidget);

        int nb_item = 0;
        int y = 0;
        int font_size = 12;
        QFont font;
        font.setPointSize(font_size);

        foreach(const QString& key, items.keys()) {

            image = new QLabel(Dialog);
            image->setPixmap((QPixmap(QApplication::applicationDirPath() + "/ressources/items/" + key + ".png")));
            image->setObjectName(key);
            gridLayout->addWidget(image, nb_item, 0);

            text = new QLabel(Dialog);
            text->setText("This item, " + key + ", gives you " + QString::number(doc["items"][key]["attack_point"].toInt()) + " attack points, " + QString::number(doc["items"][key]["brain_point"].toInt()) + " brain points, " + QString::number(doc["items"][key]["strength_point"].toInt()) + " strength points and " + QString::number(doc["items"][key]["life_point"].toInt()) + " life points.");
            text->setObjectName(key);
            text->setFont(font);
            gridLayout->addWidget(text, nb_item, 1);

            nb_item ++;

            if (y < text->text().length()){

                y = text->text().length();

            }

        }

        close_button = new QPushButton(Dialog);
        close_button->setText("Understood");
        gridLayout->addWidget(close_button, nb_item - 1, y * font_size);

        connect(close_button, &QPushButton::clicked, this, &InfoItems::close);

        setFixedSize(y * (font_size / 1.4), nb_item * 40 + 10 * abs(nb_item - 2));
        setWindowTitle("Items list");
        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    }

// Dans la partie privée, on retrouve la fonction  pour fermer la fenêtre
private:

    Ui::InfoItems *ui;

    // Fonction pour fermer la fenêtre de dialogue
    void close(){

        this->done(1);

    }

};

#endif // INFOITEMS_H
