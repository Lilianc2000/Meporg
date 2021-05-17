#ifndef MAINWINDOWVYWGET_H
#define MAINWINDOWVYWGET_H

// On inclus toutes les librairies nécessaires au projet

#include <QtCore/QVariant>
#include <QAction>
#include <QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "aboutwindow.h"
#include <QMessageBox>
#include <QProcess>
#include <QFontDatabase>
#include <QInputDialog>
#include <QMediaPlayer>
#include <QProgressBar>
#include "game.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QObject>
#include "itembutton.h"
#include "infoitems.h"

// On défini le namespace pour QT

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

// On initialise la classe MainWindow

class MainWindow : public QMainWindow
{

    Q_OBJECT

// Dans la partie public, on retrouve tout ce qui relève de l'affichage
public:

    // On commence par définir nos objets d'interface

    // Partie du menu en haut de la fenêtre
    QAction *actionReset;
    QAction *actionExit;
    QAction *actionAuthors;
    QAction *actionVersion;
    QAction *actionItems;
    QAction *actionScore;
    QMenuBar *menubar;
    QMenu *menu_principal;
    QMenu *menu_about;

    // Partie centrale de l'application
    QWidget *centralwidget;
    QLabel *background;

    // Partie textuelle (page d'accueil)
    QLabel *WelcomeLabel;
    QLabel *label;
    QLabel *HighScore;

    // Partie d'affichage des images du choix du type de héro (page d'accueil)
    QWidget *horizontalLayoutPictureWidget;
    QHBoxLayout *horizontalLayoutPicture;
    QLabel *human;
    QLabel *wolf;
    QLabel *werewolf;
    QLabel *demon;

    // Partie d'affichage des boutons du choix du type de héro (page d'accueil)
    QHBoxLayout *horizontalLayoutButton;
    QWidget *horizontalLayoutButtonWidget;
    QPushButton *button_human;
    QPushButton *button_werewolf;
    QPushButton *button_wolf;
    QPushButton *button_demon;

    // Partie des boutons d'attaque (page de combat)
    QPushButton *Attack1;
    QPushButton *Attack2;
    QPushButton *Attack3;
    QPushButton *Attack4;

    // Information sur le déroulé du combat
    QTextBrowser *Information;

    // Affichage du héro et de l'ennemi, avec leur bar de vie (page de combat)
    QLabel *Enemy;
    QLabel *Hero;
    QProgressBar *Enemy_life;
    QProgressBar *Hero_life;
    QLabel *Enemy_life_label;
    QLabel *Hero_life_label;

    // Lecture de la musique d'ambiance
    QMediaPlayer *musique = new QMediaPlayer;

    // Ensuite, on défini nos fonctions d'affichage

    // Déclaration du constructeur et du destructeur
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Fonction pour initialiser la page d'accueil de l'application
    void ui_accueil(QMainWindow *MainWindow)
    {

        // On récupère notre police personnalisé à l'application
        QString family = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(QApplication::applicationDirPath() + "/ressources/font.ttf")).at(0);
        QFont font1(family);
        QFont font2(family);
        QFont font4(family);

        // On lance la musique d'accueil
        musique->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/accueil/start_sound.wav"));
        musique->setVolume(20);
        musique->play();

        // Si c'est la première fenêtre que l'on ouvre, on défini son nom
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");

        // On initialise le menu
        actionReset = new QAction(MainWindow); 
        actionExit = new QAction(MainWindow);      
        actionAuthors = new QAction(MainWindow);     
        actionVersion = new QAction(MainWindow);
        actionItems = new QAction(MainWindow);
        actionScore = new QAction(MainWindow);

        actionVersion->setObjectName("actionVersion");
        actionExit->setObjectName("actionExit");
        actionAuthors->setObjectName("actionAuthors");
        actionReset->setObjectName("actionReset");
        actionItems->setObjectName("actionItems");
        actionScore->setObjectName("actionScore");

        actionReset->setText("Reset Game");
        actionExit->setText("Exit");
        actionAuthors->setText("Authors");
        actionVersion->setText("Version");
        actionItems->setText("Items");
        actionScore->setText("Reset High Score");

        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1085, 22));

        menu_principal = new QMenu(menubar);
        menu_about = new QMenu(menubar);

        menu_about->setObjectName("menu_about");
        menu_principal->setObjectName("menu_principal");

        menubar->addAction(menu_principal->menuAction());
        menubar->addAction(menu_about->menuAction());

        menu_principal->addAction(actionScore);
        menu_principal->addAction(actionReset);
        menu_principal->addAction(actionExit);
        menu_principal->setTitle("Menu");

        menu_about->addAction(actionItems);
        menu_about->addAction(actionAuthors);
        menu_about->addAction(actionVersion);
        menu_about->setTitle("About");

        MainWindow->setMenuBar(menubar);

        // On initialise le coeur de l'accueil avec un widget principal, un label pour le background, deux labels pour les messages d'accueil
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");

        background = new QLabel(centralwidget);
        background->setObjectName("label_2");
        background->setGeometry(QRect(0, 0, 1024, 768));
        background->setMouseTracking(false);
        background->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/accueil/main_background.png"));

        WelcomeLabel = new QLabel(centralwidget);
        WelcomeLabel->setObjectName("WelcomeLabel");
        WelcomeLabel->setGeometry(QRect(30, 10, 821, 201));
        font1.setPointSize(72);
        WelcomeLabel->setFont(font1);
        WelcomeLabel->setText("Welcome to Meporg");

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 350, 691, 91));
        font2.setPointSize(38);
        label->setFont(font2);
        label->setText("Please, select your hero");

        // On initialise l'affichage des images du choix du type de héro, et les layouts pour l'agencement automatique de ces derniers
        horizontalLayoutPictureWidget = new QWidget(centralwidget);
        horizontalLayoutPictureWidget->setObjectName("horizontalLayoutPictureWidget");
        horizontalLayoutPictureWidget->setGeometry(QRect(40, 520, 1031, 110));
        horizontalLayoutPicture = new QHBoxLayout(horizontalLayoutPictureWidget);
        horizontalLayoutPicture->setSpacing(100);
        horizontalLayoutPicture->setObjectName("horizontalLayourPicture");
        horizontalLayoutPicture->setContentsMargins(20, 0, 20, 0);

        human = new QLabel(centralwidget);
        human->setObjectName("human_picture");
        human->setGeometry(QRect(0, 0, 100, 101));
        human->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/accueil/human.png"));
        horizontalLayoutPicture->addWidget(human);

        werewolf = new QLabel(centralwidget);
        werewolf->setObjectName("werewolf_picture");
        werewolf->setGeometry(QRect(0, 0, 100, 163));
        werewolf->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/accueil/werewolf.png"));
        horizontalLayoutPicture->addWidget(werewolf);

        wolf = new QLabel(centralwidget);
        wolf->setObjectName("wolf_picture");
        wolf->setGeometry(QRect(0, 0, 98, 81));
        wolf->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/accueil/wolf.png"));
        horizontalLayoutPicture->addWidget(wolf);

        demon = new QLabel(centralwidget);
        demon->setObjectName("demon_picture");
        demon->setGeometry(QRect(0, 0, 100, 117));
        demon->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/accueil/demon.png"));
        horizontalLayoutPicture->addWidget(demon);

        // On fait de même avec les bouttons
        horizontalLayoutButtonWidget = new QWidget(centralwidget);
        horizontalLayoutButtonWidget->setObjectName("horizontalLayoutButtonWidget");
        horizontalLayoutButtonWidget->setGeometry(QRect(0, 620, 1031, 80));
        horizontalLayoutButton = new QHBoxLayout(horizontalLayoutButtonWidget);
        horizontalLayoutButton->setSpacing(100);
        horizontalLayoutButton->setObjectName("horizontalLayoutButton");
        horizontalLayoutButton->setContentsMargins(20, 0, 20, 0);

        QFont font3;
        font3.setFamily("Sitka Display");
        font3.setPointSize(16);

        button_human = new QPushButton(horizontalLayoutButtonWidget);
        button_human->setObjectName("button_human");
        button_human->setFont(font3);
        horizontalLayoutButton->addWidget(button_human);

        button_werewolf = new QPushButton(horizontalLayoutButtonWidget);
        button_werewolf->setObjectName("button_werewolf");
        button_werewolf->setFont(font3);
        horizontalLayoutButton->addWidget(button_werewolf);

        button_wolf = new QPushButton(horizontalLayoutButtonWidget);
        button_wolf->setObjectName("button_wolf");
        button_wolf->setFont(font3);
        horizontalLayoutButton->addWidget(button_wolf);

        button_demon = new QPushButton(horizontalLayoutButtonWidget);
        button_demon->setObjectName("button_demon");
        button_demon->setFont(font3);
        horizontalLayoutButton->addWidget(button_demon);

        button_human->setText("Human");
        button_werewolf->setText("Werewolf");
        button_wolf->setText("Wolf");
        button_demon->setText("Demon");

        // On connecte l'ensemble de nos boutons à leurs fonctions
        connect(button_demon, &QPushButton::clicked, this, &MainWindow::demon_function);
        connect(button_human, &QPushButton::clicked, this, &MainWindow::human_function);
        connect(button_werewolf, &QPushButton::clicked, this, &MainWindow::werewolf_function);
        connect(button_wolf, &QPushButton::clicked, this, &MainWindow::wolf_function);
        connect(actionAuthors, &QAction::triggered, this, &MainWindow::about_authors);
        connect(actionVersion, &QAction::triggered, this, &MainWindow::version);
        connect(actionExit, &QAction::triggered, this, &MainWindow::exit);
        connect(actionReset, &QAction::triggered, this, &MainWindow::reset);
        connect(actionItems, &QAction::triggered, this, &MainWindow::info_items);
        connect(actionScore, &QAction::triggered, this, &MainWindow::reset_high_score);

        // On mets le high score
        HighScore = new QLabel(centralwidget);
        QJsonDocument doc = Reader::readDataJson();
        HighScore->setText("High score : " + QString::number(doc["highscore"].toInt()));
        int font4_point_size = 16;
        HighScore->setGeometry(MainWindow->width() * 1.37, font4_point_size, HighScore->text().length() * font4_point_size, font4_point_size);
        font4.setPointSize(font4_point_size);
        HighScore->setFont(font4);


        // Puis on set le tout sur la fenêtre
        MainWindow->setCentralWidget(centralwidget);

    }

    // Fonction pour initialiser la page de combat de l'application
    void ui_combat(QMainWindow *MainWindow)
       {
           // On lance la musique de combat
           musique->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/fight/main_sound.wav"));
           musique->play();

           // On initialize un nouveau widget central
           centralwidget = new QWidget(MainWindow);
           centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

           // On y met l'arrière plan de combat
           background = new QLabel(centralwidget);
           background->setObjectName("label_2");
           background->setGeometry(QRect(0, 0, 1024, 768));
           background->setMouseTracking(false);
           background->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/fight/fight_background.png"));

           // On initialise les 4 boutons d'attaques
           QFont font;
           font.setPointSize(16);
           Attack1 = new QPushButton(centralwidget);
           Attack1->setObjectName(QString::fromUtf8("Attack1"));
           Attack1->setGeometry(QRect(700, 610, 151, 61));
           Attack1->setFont(font);

           Attack2 = new QPushButton(centralwidget);
           Attack2->setObjectName(QString::fromUtf8("Attack2"));
           Attack2->setGeometry(QRect(860, 610, 151, 61));
           Attack2->setFont(font);

           Attack3 = new QPushButton(centralwidget);
           Attack3->setObjectName(QString::fromUtf8("Attack3"));
           Attack3->setGeometry(QRect(700, 675, 151, 61));
           Attack3->setFont(font);

           Attack4 = new QPushButton(centralwidget);
           Attack4->setObjectName(QString::fromUtf8("Attack4"));
           Attack4->setGeometry(QRect(860, 675, 151, 61));
           Attack4->setFont(font);

           // On initialise la fenêtre d'information en combat
           Information = new QTextBrowser(centralwidget);
           Information->setObjectName(QString::fromUtf8("Information"));
           Information->setGeometry(QRect(10, 615, 631, 122));

           // On initialise l'affichage de l'ennemi, du héro et de leur barre de vie
           Enemy = new QLabel(centralwidget);
           Enemy->setObjectName(QString::fromUtf8("Enemy"));
           Enemy->setGeometry(QRect(700, 20, 350, 350));

           Hero = new QLabel(centralwidget);
           Hero->setObjectName(QString::fromUtf8("Hero"));
           Hero->setGeometry(QRect(30, 230, 350, 350));

           Enemy_life = new QProgressBar(centralwidget);
           Enemy_life->setObjectName(QString::fromUtf8("Enemy_life"));
           Enemy_life->setGeometry(QRect(690, 370, 330, 16));
           Enemy_life->setStyleSheet("QProgressBar{ border-radius: 5px; text-align : center;} QProgressBar::chunk {background-color: red; width: 20px;}");

           Enemy_life_label = new QLabel(centralwidget);
           Enemy_life_label->setText("Enemy's remaining life :");
           Enemy_life_label->setObjectName("enemy_label");
           Enemy_life_label->setGeometry(QRect(690, 350, 350, 16));
           Enemy_life_label->setStyleSheet("QLabel { color : white; font : bold;}");

           Hero_life = new QProgressBar(centralwidget);
           Hero_life->setObjectName(QString::fromUtf8("Hero_life"));
           Hero_life->setGeometry(QRect(20, 580, 350, 16));
           Hero_life->setStyleSheet("QProgressBar{ border-radius: 5px; text-align : center;} QProgressBar::chunk {background-color: red; width: 20px;}");

           Hero_life_label = new QLabel(centralwidget);
           Hero_life_label->setText("Your remaining life :");
           Hero_life_label->setObjectName("hero_label");
           Hero_life_label->setGeometry(QRect(20, 560, 350, 16));
           Hero_life_label->setStyleSheet("QLabel { color : white; font : bold; }");

           // On retire la possibilité de reset le high score
           menu_principal->removeAction(actionScore);

           // Puis on set le tout sur la fenêtre
           MainWindow->setCentralWidget(centralwidget);

    }


// Dans la partie privée, on retrouve toutes les déclarations de fonctions et des variables qui seront utiles dans le jeu (détaillés dans le fichier mainwindow.cpp)
private:

    Entity *hero;
    std::vector<Entity*> ennemies;
    Entity *actual_ennemy;
    unsigned long long actual_ennemy_position = -1;
    QPropertyAnimation *enemy_animation;
    QPropertyAnimation *heroGoFight_animation;
    QPropertyAnimation *heroEndFight_animation;
    QSequentialAnimationGroup *heroFight_animation;
    QPropertyAnimation *enemyGoFight_animation;
    QPropertyAnimation *enemyEndFight_animation;
    QSequentialAnimationGroup *enemyFight_animation;
    QMediaPlayer *hero_fight;
    QMediaPlayer *enemy_fight;

    Ui::MainWindow *ui;
    void demon_function();
    void werewolf_function();
    void human_function();
    void wolf_function();
    void version();
    void about_authors();
    void play(std::string type, std::string name, std::string job);
    void exit();
    void reset();
    QString get_name();
    QString get_job();
    void attack1();
    void attack2();
    void attack3();
    void attack4();
    void get_next_ennemy();
    void defeat();
    void victory();
    void enemy_die();
    void change_enemy();
    void setupFightAnimation();
    void attack_next_part();
    void activate_attack();
    void start_attack();
    void check_hero_die();
    void set_enemy_life();
    void info_items();
    void reset_high_score();

// Dans la partie public slots, on retrouve les fonctions qui seront appelé pour nos signaux personnalisés
public slots:
    void show_enemy_item();
    void new_item(Item *x);
    void new_item();

};

#endif // MAINWINDOWVYWGET_H
