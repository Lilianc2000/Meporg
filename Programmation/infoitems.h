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

    // On crée les widgets de la fenêtre
    // Partie centrale de la fenêtre
    QWidget *centralwidget;
    QGridLayout *gridLayout;

    // Bouton de fermeture de la fenêtre
    QPushButton *close_button;

    // Label pour chaque objet
    QLabel *image;
    QLabel *text;

    // Constructeur et destructeur
    InfoItems(QWidget *parent = nullptr);
    ~InfoItems();

    // Fonction pour initialiser la fenêtre
    void setup_info(QDialog *Dialog){

        Dialog->setObjectName("ItemsInfo");

        // Partie lecture du JSON
        QJsonDocument doc = Reader::readDataJson();
        QJsonObject items = doc["items"].toObject();

        // On initialise le coeur de la page, avec un widget pricipal et un grid layout pour agencer automatiquement nos objets
        centralwidget = new QWidget(Dialog);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);

        // Varbiable diverses
        int nb_item = 0;
        int y = 0;
        int font_size = 12;
        QFont font;
        font.setPointSize(font_size);

        // Pour chaque item dans le JSON, on le traite
        foreach(const QString& key, items.keys()) {

            // On crée un nouveau pointeur pour l'image de l'objet, et on le met après le précédent
            image = new QLabel(Dialog);
            image->setPixmap((QPixmap(QApplication::applicationDirPath() + "/ressources/items/" + key + ".png")));
            image->setObjectName(key);
            gridLayout->addWidget(image, nb_item, 0);

            // On crée un nouveau pointeur pour le texte de l'objet, et on le met après le précédent
            text = new QLabel(Dialog);
            text->setText("This item, " + key + ", gives you " + QString::number(doc["items"][key]["attack_point"].toInt()) + " attack points, " + QString::number(doc["items"][key]["brain_point"].toInt()) + " brain points, " + QString::number(doc["items"][key]["strength_point"].toInt()) + " strength points and " + QString::number(doc["items"][key]["life_point"].toInt()) + " life points.");
            text->setObjectName(key);
            text->setFont(font);
            gridLayout->addWidget(text, nb_item, 1);

            nb_item ++;

            // On garde en mémoire la longueur maximal des textes, cela servira a la taille de la fenêtre
            if (y < text->text().length()){

                y = text->text().length();

            }

        }

        // On créer le bouton de fermeture de la fenêtre
        close_button = new QPushButton(Dialog);
        close_button->setText("Understood");
        gridLayout->addWidget(close_button, nb_item - 1, y * font_size);
        connect(close_button, &QPushButton::clicked, this, &InfoItems::close);

        // On règle la fenêtre
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
