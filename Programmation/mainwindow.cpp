#include "mainwindow.h"

// Constructeur de la fenêtre principale du jeu
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){

    // On setup la fenêtre avec l'ui d'accueil défini dans le .h
    ui_accueil(this);
    setFixedSize(1024, 768);
    setWindowTitle("MePorg");

    // On initialise nos mediaplayers des sons des combats
    hero_fight = new QMediaPlayer;
    enemy_fight = new QMediaPlayer;
    hero_fight->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/fight/hero_fight.wav"));
    enemy_fight->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/fight/enemy_fight.wav"));
    enemy_fight->setVolume(40);
    hero_fight->setVolume(40);

}

// Destructeur de la classe
MainWindow::~MainWindow(){
    delete ui;
}

// Fonction pour indiquer que le hero sera un demon
void MainWindow::demon_function(){

    qDebug() << "Demon pressed";

    // On demande le nom du joueur
    QString name = get_name();
    qDebug() << "Name : " << name;

    // On demande le métier du joueur
    QString job = get_job();
    qDebug() << "Job : " << job;

    // On lance le jeu
    play("Demon", name.toStdString(), job.toStdString());

}

// Fonction pour indiquer que le hero sera un humain
void MainWindow::human_function(){

    qDebug() << "Human pressed";

    // On demande le nom du joueur
    QString name = get_name();
    qDebug() << "Name : " << name;

    // On demande le métier du joueur
    QString job = get_job();
    qDebug() << "Job : " << job;

    // On lance le jeu
    play("Human", name.toStdString(), job.toStdString());

}

// Fonction pour indiquer que le hero sera un loup-garou
void MainWindow::werewolf_function(){

    qDebug() << "Werewolf pressed";

    // On demande le nom du joueur
    QString name = get_name();
    qDebug() << "Name : " << name;

    // On demande le métier du joueur
    QString job = get_job();
    qDebug() << "Job : " << job;

    // On lance le jeu
    play("Werewolf", name.toStdString(), job.toStdString());
}

// Fonction pour indiquer que le hero sera un loup
void MainWindow::wolf_function(){

    qDebug() << "Wolf pressed";

    // On demande le nom du joueur
    QString name = get_name();
    qDebug() << "Name : " << name;

    // On demande le métier du joueur
    QString job = get_job();
    qDebug() << "Job : " << job;

    // On lance le jeu
    play("Wolf", name.toStdString(), job.toStdString());

}

// Fonction initialisant la phase de combat
void MainWindow::play(std::string type, std::string name, std::string job){

    // On tire un nombre aléatoire d'ennemis, entre 1 et 30
    srand((unsigned long long int)time(0));
    unsigned long long int nb_ennemies = rand() % 30 + 1;

    // On initialise le héros et les ennemis
    qDebug() << "Initializing hero";
    hero = Game::createHero(name, type, job);
    qDebug() << "Hero initialized";

    qDebug() << "Initializing enemies";
    ennemies = Game::createEnemies(nb_ennemies);
    qDebug() << "Ennemies initialized";

    // On affiche la fenêtre de combat
    ui_combat(this) ;
    setFixedSize(1024, 768);

    // On initialise les animations de combat
    setupFightAnimation();

    // On vérifie le type du héros, et on affiche l'image correspondante
    HeroDemon *aa = dynamic_cast<HeroDemon*>(hero);
    HeroHuman *bb = dynamic_cast<HeroHuman*>(hero);
    HeroWolf *cc = dynamic_cast<HeroWolf*>(hero);
    HeroWerewolf *dd = dynamic_cast<HeroWerewolf*>(hero);

    if (aa != nullptr){

        Hero->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/fight/demon.png"));
        qDebug() << "Loading demon picture into hero";

    }
    else if (bb != nullptr){

        Hero->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/fight/human.png"));
        qDebug() << "Loading human picture into hero";

    }
    else if (cc != nullptr){

        Hero->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/fight/wolf.png"));
        qDebug() << "Loading wolf picture into hero";

    }
    else if (dd != nullptr){

        Hero->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/fight/werewolf.png"));
        qDebug() << "Loading werewolf picture into hero";

    }

    // On récupère le premier ennemi (on décale d'abord son label car la fonction get_next_ennemy contient une animation pour le ramener
    Enemy->move(Enemy->x() + 500, Enemy->y());
    get_next_ennemy();

    // On affiche le nom des attaques sur leur boutton
    Attack1->setText(hero->getNameAttack1());
    Attack2->setText(hero->getNameAttack2());
    Attack3->setText(hero->getNameAttack3());
    Attack4->setText(hero->getNameAttack4());

    // On affiche ce que fait une attaque lorsque la souris survole le bouton
    Attack1->setToolTip(hero->getEffectAttack1());
    Attack2->setToolTip(hero->getEffectAttack2());
    Attack3->setToolTip(hero->getEffectAttack3());
    Attack4->setToolTip(hero->getEffectAttack4());

    // On connecte les boutons à leur attaque
    connect(Attack1, &QPushButton::clicked, this, &MainWindow::attack1);
    connect(Attack2, &QPushButton::clicked, this, &MainWindow::attack2);
    connect(Attack3, &QPushButton::clicked, this, &MainWindow::attack3);
    connect(Attack4, &QPushButton::clicked, this, &MainWindow::attack4);

    // On initialise les barres de vies des héros et ennemis
    Hero_life->setMaximum(hero->getLifePoint());
    qDebug() << "Hero life : " << hero->getLifePoint();

    Enemy_life->setMaximum(actual_ennemy->getLifePoint());
    qDebug() << "Enemy life : " << actual_ennemy->getLifePoint();

    Hero_life->setTextVisible(true);
    Enemy_life->setTextVisible(true);

    Hero_life->setValue(hero->getLifePoint());
    Enemy_life->setValue(actual_ennemy->getLifePoint());

    // On indique que, lorsque la valeur de la barre change, si le héros est mort
    connect(Hero_life, &QProgressBar::valueChanged, this, &MainWindow::check_hero_die);

}

// Fonction permettant d'initialiser les animations en combat
void MainWindow::setupFightAnimation(){

    // On défini l'animation du début du combat du héro
    heroGoFight_animation = new QPropertyAnimation(Hero, "geometry");
    heroGoFight_animation->setDuration(100);
    heroGoFight_animation->setStartValue(QRect(Hero->x(), Hero->y(), Hero->width(), Hero->height()));
    heroGoFight_animation->setEndValue(QRect(Hero->x() + 30, Hero->y() - 30, Hero->width(), Hero->height()));

    // On défini l'animation de la fin du combat du héro
    heroEndFight_animation = new QPropertyAnimation(Hero, "geometry");
    heroEndFight_animation->setDuration(100);
    heroEndFight_animation->setStartValue(QRect(Hero->x() + 30, Hero->y() - 30, Hero->width(), Hero->height()));
    heroEndFight_animation->setEndValue(QRect(Hero->x(), Hero->y(), Hero->width(), Hero->height()));

    // On les regroupe dans un groupe d'animation
    heroFight_animation = new QSequentialAnimationGroup;
    heroFight_animation->addAnimation(heroGoFight_animation);
    heroFight_animation->addAnimation(heroEndFight_animation);

    // On fait de même pour les ennemis
    enemyGoFight_animation = new QPropertyAnimation(Enemy, "geometry");
    enemyGoFight_animation->setDuration(100);
    enemyGoFight_animation->setStartValue(QRect(Enemy->x(), Enemy->y(), Enemy->width(), Enemy->height()));
    enemyGoFight_animation->setEndValue(QRect(Enemy->x() - 30, Enemy->y() + 30, Enemy->width(), Enemy->height()));

    enemyEndFight_animation = new QPropertyAnimation(Enemy, "geometry");
    enemyEndFight_animation->setDuration(100);
    enemyEndFight_animation->setStartValue(QRect(Enemy->x() - 30, Enemy->y() + 30, Enemy->width(), Enemy->height()));
    enemyEndFight_animation->setEndValue(QRect(Enemy->x(), Enemy->y(), Enemy->width(), Enemy->height()));

    enemyFight_animation = new QSequentialAnimationGroup;
    enemyFight_animation->addAnimation(enemyGoFight_animation);
    enemyFight_animation->addAnimation(enemyEndFight_animation);

    // On donne les directives a suivre lorsque les animations sont finies
    // Lorsque l'animation de l'attaque du héros est finie, on peut passer à la partie d'attaque de l'ennemi
    connect(heroFight_animation, &QSequentialAnimationGroup::finished, this, &MainWindow::attack_next_part);
    // Lorsque l'animation de l'attaque de l'ennemi est finie, on peut reactiver les attaques
    connect(enemyFight_animation, &QSequentialAnimationGroup::finished, this, &MainWindow::activate_attack);

}

// Fonction permettant de récupérer l'ennemi suivant dans la liste
void MainWindow::get_next_ennemy(){

    qDebug() << "Getting next ennemy";

    // On prend l'ennemi à la position suivante
    actual_ennemy_position += 1;

    // Si on dépasse l'ensemble des ennemis, alors on a gagné
    if (actual_ennemy_position >= ennemies.size()){

        victory();

    }
    else {

        // Sinon, on récupère l'ennemi à cette position
        actual_ennemy = ennemies.at(actual_ennemy_position);

        qDebug() << "Checking ennemy type";

        // On regarde son type et on charge l'image associé
        if (actual_ennemy->getType() == "Demon"){

           qDebug() << "Loading demon picture into Enemy";
           Enemy->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/fight/demon.png"));

        }
        else if (actual_ennemy->getType() == "Human"){

            qDebug() << "Loading human picture into Enemy";
            Enemy->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/fight/human.png"));

        }
        else if (actual_ennemy->getType() == "Wolf"){

            qDebug() << "Loading wolf picture into Enemy";
            Enemy->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/fight/wolf.png"));

        }
        else if (actual_ennemy->getType() == "Werewolf"){

            qDebug() << "Loading werewolf picture into Enemy";
            Enemy->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/fight/werewolf.png"));

        }

        // On lance l'animation qui permet à l'ennemi de revenir sur le terrain
        enemy_animation = new QPropertyAnimation(Enemy, "geometry");
        enemy_animation->setDuration(750);
        enemy_animation->setStartValue(QRect(Enemy->x(), Enemy->y(), Enemy->width(), Enemy->height()));
        enemy_animation->setEndValue(QRect(Enemy->x() - 500, Enemy->y(), Enemy->width(), Enemy->height()));
        enemy_animation->start();
        connect(enemy_animation, &QPropertyAnimation::finished, this, &MainWindow::activate_attack);

        // On affiche que un ennemi est apparu
        Information->append(QString::fromStdString(actual_ennemy->getName()) + " has spawn ! What do you want to do ?");

        // On met à jour sa barre de vie
        Enemy_life->setMaximum(actual_ennemy->getLifePoint());
        Enemy_life->setValue(actual_ennemy->getLifePoint());

        // On change le titre de la fenêtre en mettant son nom
        setWindowTitle(QString::fromStdString("MePorg - Fight !                                                                                               " + hero->getName() + " vs " + actual_ennemy->getName()));

    }
}

// Fonction permettant de faire attaquer l'ennemi
void MainWindow::attack_next_part(){

    // Si l'ennemi est mort, il n'attaque pas et on traite le cas
    if (actual_ennemy->isDead()){

        enemy_die();

    }
    else{

        // Sinon, on récupère le nom de l'attaque qu'il utilise, et les dommages effectués au héro
        auto [name_attack,dmg] = actual_ennemy->enemyAttack(*hero);

        // On met à jour la vie du héro
        unsigned long long int initial_life = hero->getLifePoint();
        hero->setLifePoint(dmg);
        unsigned long long int remaning_life = hero->getLifePoint();

        // On indique que l'ennemi a attaqué, et que l'on a perdu de la vie (ou pas)
        Information->append(QString::fromStdString(actual_ennemy->getName()) + " used " + name_attack);
        Information->append("You loose " + QString::number(initial_life - remaning_life) + " hp");

        // On lance le bruit de combat et l'animation
        enemy_fight->play();
        enemyFight_animation->start();

        // On met à jour la barre de vie du héro
        if (hero->getLifePoint() > 0){

            Hero_life->setValue(hero->getLifePoint());

        }
        else{

            Hero_life->setValue(0);

        }


    }

}

// Fonction pour vérifier si le heros est mort
void MainWindow::check_hero_die(){

    qDebug() << "Checking if hero is dead";

    // Si il est mort, alors on a perdu
    if (hero->isDead()){

        qDebug() << "Hero is dead";
        defeat();

    }
    qDebug() << "Hero is not dead";
}

// Fonction pour effectuer le début d'une attaque
void MainWindow::start_attack(){

    // On désactive tous les boutons d'attaques, pour éviter d'en lancer plusieurs à la fois et d'avoir des conflits
    Attack1->setEnabled(false);
    Attack2->setEnabled(false);
    Attack4->setEnabled(false);
    Attack3->setEnabled(false);

    // On lance le bruit et l'animation de l'attaque
    hero_fight->play();
    heroFight_animation->start();

}

// Fonction pour mettre à jour la barre de vie de l'ennemi
void MainWindow::set_enemy_life(){

    // Si la vie est supérieur à 0, alors on met à jour la barre de vie
    if (actual_ennemy->getLifePoint() > 0){

        Enemy_life->setValue(actual_ennemy->getLifePoint());

    }
    // Sinon, on met 0 (le widget QProgressBar ne semble pas gérer les nombres négatifs)
    else{

        Enemy_life->setValue(0);

    }

}

// Fonction de l'attaque 1
void MainWindow::attack1(){

    // On effectue la première partie de l'attaque
    start_attack();

    qDebug() << "Attack 1 pressed";

    // On inflige les dommages de l'attaque à l'ennemi
    Information->append("You choose " + Attack1->text());
    unsigned long long int initial_life = actual_ennemy->getLifePoint();
    actual_ennemy->setLifePoint(hero->attack1(*actual_ennemy));
    set_enemy_life();
    unsigned long long int remaning_life = actual_ennemy->getLifePoint();
    Information->append("Enemy loose " + QString::number(initial_life - remaning_life) + " hp");

}

// Fonction de l'attaque 2
void MainWindow::attack2(){

    // On effectue la première partie de l'attaque
    start_attack();

    qDebug() << "Attack 2 pressed";

    // On inflige les dommages de l'attaque à l'ennemi
    Information->append("You choose " + Attack2->text());
    unsigned long long int initial_life = actual_ennemy->getLifePoint();
    actual_ennemy->setLifePoint(hero->attack2(*actual_ennemy));
    set_enemy_life();
    unsigned long long int remaning_life = actual_ennemy->getLifePoint();
    Information->append("Enemy loose " + QString::number(initial_life - remaning_life) + " hp");

}

// Fonction de l'attaque 3
void MainWindow::attack3(){

    // On effectue la première partie de l'attaque
    start_attack();

    qDebug() << "Attack 3 pressed";

    // On inflige les dommages de l'attaque à l'ennemi
    Information->append("You choose " + Attack3->text());
    unsigned long long int initial_life = actual_ennemy->getLifePoint();
    actual_ennemy->setLifePoint(hero->attack3(*actual_ennemy));
    set_enemy_life();
    unsigned long long int remaning_life = actual_ennemy->getLifePoint();
    Information->append("Enemy loose " + QString::number(initial_life - remaning_life) + " hp");

}

// Fonction de l'attaque 4
void MainWindow::attack4(){

    // On effectue la première partie de l'attaque
    start_attack();

    qDebug() << "Attack 4 pressed";

    // On inflige les dommages de l'attaque à l'ennemi
    Information->append("You choose " + Attack4->text());
    unsigned long long int initial_life = actual_ennemy->getLifePoint();
    actual_ennemy->setLifePoint(hero->attack4(*actual_ennemy));
    set_enemy_life();
    unsigned long long int remaning_life = actual_ennemy->getLifePoint();
    Information->append("Enemy loose " + QString::number(initial_life - remaning_life) + " hp");

}

// Fonction permettant d'annoncer la mort de l'ennemi
void MainWindow::enemy_die(){

    // On annonce la mort de l'ennemi
    qDebug() << "Ennemy is dead";
    Information->append(QString::fromStdString(actual_ennemy->getName()) + " has defited !");

    // On change l'ennemi
    change_enemy();

}

// Fonction pour le menu About / Authors
void MainWindow::about_authors(){

    // On initialise une nouvelle fenêtre de type AboutWindow
    AboutWindow *w = new AboutWindow(this);

    // On l'affiche
    w->show();

}

// Fonction pour le menu About / Info Items
void MainWindow::info_items(){

    // On initialise une nouvelle fenêtre de type InfoItems
    InfoItems *w = new InfoItems(this);

    // On l'affiche
    w->show();

}

// Fonction pour le menu About / Version
void MainWindow::version(){

    // On ouvre une QMessageBox indiquant la version du logiciel
    QMessageBox msg;
    msg.setWindowTitle("Version");
    msg.setText("Release 1.1");
    msg.setIcon(QMessageBox::Information);
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();

}

// Fonction pour quitter le programme
void MainWindow::exit(){

    // On appelle la méthode static de QApplication, quit()
    QApplication::quit();

}

// Fonction pour redémarrer le programme
void MainWindow::reset(){

    // On démarre un nouveau processus de l'application
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

    // On arrête celui ci
    exit();

}

// Fonction pour récupérer le nom du joueur
QString MainWindow::get_name(){

    // On récupère l'entrée de l'utilisateur
    QString text = QInputDialog::getText(this,"Type your name","Name ?                                                  ");

    // S'il ne rentre rien, il sera appelé "The Anonymous", on l'averti
    if(text == ""){

        QMessageBox::warning(this, "No name typed", "You will be \"The Anonymous\"");
        text = QString("The Anonymous");

    }

    return text;

}

// Fonction pour signifier la victoire du joueur
void MainWindow::victory(){

    // On lance la musique de victoire
    musique->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/victory_sound.wav"));
    musique->play();

    // On initialise la fenêtre de victoire, qui propose de relancer ou de quitter
    QMessageBox msg;
    msg.setWindowTitle("Victory !");
    msg.setText("You win ! GG WP ! Feel free to try again, it may be harder next time :)");
    msg.setIcon(QMessageBox::Information);
    msg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    // Les boutons de la fenêtre de victoire
    QPushButton *restart = new QPushButton();
    restart->setObjectName("button_restart");
    restart->setText("Restart");
    QPushButton *exit = new QPushButton();
    exit->setObjectName("button_exit");
    exit->setText("Exit");

    connect(exit, &QPushButton::clicked, this, &MainWindow::exit);
    connect(restart, &QPushButton::clicked, this, &MainWindow::reset);

    msg.addButton(exit, QMessageBox::NoRole);
    msg.addButton(restart, QMessageBox::YesRole);

    // On enregistre le meilleur score
    Game::setHighScore(actual_ennemy_position);

    // On affiche la fenêtre de dialog
    msg.exec();
}

// Fonction pour signifier la défaite du joueur
void MainWindow::defeat(){

    // On lance la musique de défaite
    musique->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/death_sound.wav"));
    musique->play();

    // On initialise la fenêtre de défaite, qui propose de relancer ou de quitter
    QMessageBox msg;
    msg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    msg.setWindowTitle("Defeat...");
    msg.setText("You loose... Feel free to try again, next time will be yours !");
    msg.setIcon(QMessageBox::Information);

    // Les boutons de la fenêtre de victoire
    QPushButton *restart = new QPushButton();
    restart->setObjectName("button_restart");
    restart->setText("Restart");
    QPushButton *exit = new QPushButton();
    exit->setObjectName("button_exit");
    exit->setText("Exit");

    connect(exit, &QPushButton::clicked, this, &MainWindow::exit);
    connect(restart, &QPushButton::clicked, this, &MainWindow::reset);

    msg.addButton(exit, QMessageBox::NoRole);
    msg.addButton(restart, QMessageBox::YesRole);

    // On enregistre le meilleur score
    Game::setHighScore(actual_ennemy_position);

    // On affiche la fenêtre de dialog
    msg.exec();

}

// Fonction pour récupérer le métier du joueur
QString MainWindow::get_job(){

    // On ouvre une QMessageBox avec trois boutons contenant le nom des métiers
    QMessageBox job;
    QString job_name;
    job.setWindowTitle("Job selection");
    job.setText("Select your job");
    QAbstractButton *Worker = job.addButton(tr("Worker"), QMessageBox::YesRole);
    QAbstractButton *Teacher = job.addButton(tr("Teacher"), QMessageBox::YesRole);
    QAbstractButton *Healer = job.addButton(tr("Healer"), QMessageBox::YesRole);
    job.exec();

    // On récupère le bouton cliqué
    if (job.clickedButton() == Worker){

        job_name = "Worker";

    }
    else if (job.clickedButton() == Teacher){

        job_name = "Teacher";

    }
    else if (job.clickedButton() == Healer){

        job_name = "Healer";

    }

    // On retourne le métier choisi
    return job_name;

}

// Fonction pour changer l'ennemi
void MainWindow::change_enemy(){

    // On lance l'animation de sortie de l'ennemi
    enemy_animation = new QPropertyAnimation(Enemy, "geometry");
    enemy_animation->setDuration(750);
    enemy_animation->setStartValue(QRect(Enemy->x(), Enemy->y(), Enemy->width(), Enemy->height()));
    enemy_animation->setEndValue(QRect(Enemy->x() + 500, Enemy->y(), Enemy->width(), Enemy->height()));
    enemy_animation->start();

    // Lorsque elle est fini, on demande au joueur de choisir un item porté par l'ennemi
    connect(enemy_animation, &QPropertyAnimation::finished, this, &MainWindow::show_enemy_item);

}

// Fonction pour réactiver les boutons d'attaques
void MainWindow::activate_attack(){

    // On réactive les quatres boutons d'attaques
    Attack1->setEnabled(true);
    Attack2->setEnabled(true);
    Attack4->setEnabled(true);
    Attack3->setEnabled(true);

}

// Fonction pour afficher les items de l'ennemi
void MainWindow::show_enemy_item(){

    qDebug() << "Nombre d'items de " << actual_ennemy->getType() << " : " << actual_ennemy->getItems().getNumberItems();

    // Si l'ennemi n'a pas d'item, alors on passe directement à l'affichage de l'ennemi suivant
    if (actual_ennemy->getItems().getNumberItems() == 0){

        get_next_ennemy();

    }
    else {

        // Sinon, on initialise une QMessageBox avec un bouton par item de l'ennemi
        // Ces boutons sont du type ItemButton, héritant de QPushButton, dont le signal click est redéfini de sorte qu'il puisse accepter un item en paramètre
        // Grace à ca, on peut utiliser une seule fonction permettant d'ajouter n'importe quel item au sac a dos du joueur

        ItemButton *button;

        // On initialise la messagebox
        QMessageBox msg;
        msg.setWindowTitle("Enemy carried item");
        msg.setText("What item do you want to keep ?");
        msg.setIcon(QMessageBox::Information);
        msg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        Item currentItem;

        // Pour chaque item, on ajoute un bouton à la message box
        for (unsigned long long int i = 0; i < actual_ennemy->getItems().getNumberItems(); i++){

            currentItem = actual_ennemy->getItems().getItem(i);
            button = new ItemButton(&currentItem, this);

            button->setObjectName(QString::fromStdString(actual_ennemy->getItems().getItem(i).getName()));
            button->setText(QString::fromStdString(actual_ennemy->getItems().getItem(i).getName()));

            // On affiche une description de l'item au passage de la souris sur le bouton
            button->setToolTip("This item gives you " + QString::number(actual_ennemy->getItems().getItem(i).getAttackPoint()) + " attack points, " + QString::number(actual_ennemy->getItems().getItem(i).getBrainPoint()) + " brain points, " + QString::number(actual_ennemy->getItems().getItem(i).getStrengthPoint()) + " strength points and " + QString::number(actual_ennemy->getItems().getItem(i).getLifePoint()) + " life points.");
            
            connect(button, SIGNAL(clicked(Item*)), this, SLOT(new_item(Item*)));

            msg.addButton(button, QMessageBox::YesRole);

        }

        // On ajoute un bouton permettant de ne pas choisir d'item
        button = new ItemButton(NULL, this);
        button->setObjectName("None");
        button->setText("None");

        connect(button, SIGNAL(clicked(Item*)), this, SLOT(new_item(Item*)));
        msg.addButton(button, QMessageBox::NoRole);

        // On affiche la fenêtre de dialog
        msg.exec();

    }

}

// Fonction pour ajouter un item au sac a dos du joueur
void MainWindow::new_item(Item *new_item){

    // Si le pointeur d'entrée est null, alors il n'y a pas d'item à ajouter
    if (new_item == nullptr){

        qDebug() << "None item was taken";

    }
    else{

        // Sinon, on ajouter l'item au sac a dos du héros, grace à la surdéfinition de l'opérateur +
        *hero + *new_item;
        qDebug() << QString::fromStdString(new_item->getName()) << " added to your backpack.";

    }

    // On affiche l'ennemi suivant
    get_next_ennemy();

}

// Fonction inutilisé mais obligatoire pour la surdéfinition du signal click des itembuttons
void MainWindow::new_item(){
}

// Fonction pour réinitialiser le score max
void MainWindow::reset_high_score(){

    Game::resetHighScore();
    reset();

}
