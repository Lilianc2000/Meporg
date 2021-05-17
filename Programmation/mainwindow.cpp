#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    ui_accueil(this);
    setFixedSize(1024, 768);
    setWindowTitle("MePorg");

    hero_fight = new QMediaPlayer;
    enemy_fight = new QMediaPlayer;
    hero_fight->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/fight/hero_fight.wav"));
    enemy_fight->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/fight/enemy_fight.wav"));
    enemy_fight->setVolume(40);
    hero_fight->setVolume(40);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::demon_function(){

    qDebug() << "Demon pressed";
    QString name = get_name();
    qDebug() << "Name : " << name;
    QString job = get_job();
    qDebug() << "Job : " << job;
    play("Demon", name.toStdString(), job.toStdString());

}

void MainWindow::human_function(){

    qDebug() << "Human pressed";
    QString name = get_name();
    qDebug() << "Name : " << name;
    QString job = get_job();
    qDebug() << "Job : " << job;
    play("Human", name.toStdString(), job.toStdString());

}

void MainWindow::werewolf_function(){

    qDebug() << "Werewolf pressed";
    QString name = get_name();
    qDebug() << "Name : " << name;
    QString job = get_job();
    qDebug() << "Job : " << job;
    play("Werewolf", name.toStdString(), job.toStdString());
}

void MainWindow::wolf_function(){

    qDebug() << "Wolf pressed";
    QString name = get_name();
    qDebug() << "Name : " << name;
    QString job = get_job();
    qDebug() << "Job : " << job;
    play("Wolf", name.toStdString(), job.toStdString());

}

void MainWindow::play(std::string type, std::string name, std::string job){

    srand((unsigned int)time(0));
    int nb_ennemies = rand() % 30 + 1;

    qDebug() << "Initializing hero";
    hero = Game::createHero(name, type, job);
    qDebug() << "Hero initialized";
    qDebug() << "Initializing enemies";
    ennemies = Game::createEnemies(nb_ennemies);
    qDebug() << "Ennemies initialized";

    ui_combat(this) ;
    setFixedSize(1024, 768);

    setupFightAnimation();

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

    Enemy->move(Enemy->x() + 500, Enemy->y());
    get_next_ennemy();

    Attack1->setText(hero->getNameAttack1());
    Attack2->setText(hero->getNameAttack2());
    Attack3->setText(hero->getNameAttack3());
    Attack4->setText(hero->getNameAttack4());

    Attack1->setToolTip("This attack make the enemy loose x life");
    Attack2->setToolTip("This attack make the enemy loose x life");
    Attack3->setToolTip("This attack make the enemy loose x life");
    Attack4->setToolTip("This attack make the enemy loose x life");

    connect(Attack1, &QPushButton::clicked, this, &MainWindow::attack1);
    connect(Attack2, &QPushButton::clicked, this, &MainWindow::attack2);
    connect(Attack3, &QPushButton::clicked, this, &MainWindow::attack3);
    connect(Attack4, &QPushButton::clicked, this, &MainWindow::attack4);

    Hero_life->setMaximum(hero->getLifePoint());
    qDebug() << "Hero life : " << hero->getLifePoint();
    Enemy_life->setMaximum(actual_ennemy->getLifePoint());
    qDebug() << "Enemy life : " << actual_ennemy->getLifePoint();
    Hero_life->setTextVisible(true);
    Enemy_life->setTextVisible(true);
    Hero_life->setValue(hero->getLifePoint());
    Enemy_life->setValue(actual_ennemy->getLifePoint());
    connect(Hero_life, &QProgressBar::valueChanged, this, &MainWindow::check_hero_die);

}

void MainWindow::setupFightAnimation(){

    heroGoFight_animation = new QPropertyAnimation(Hero, "geometry");
    heroGoFight_animation->setDuration(100);
    heroGoFight_animation->setStartValue(QRect(Hero->x(), Hero->y(), Hero->width(), Hero->height()));
    heroGoFight_animation->setEndValue(QRect(Hero->x() + 30, Hero->y() - 30, Hero->width(), Hero->height()));

    heroEndFight_animation = new QPropertyAnimation(Hero, "geometry");
    heroEndFight_animation->setDuration(100);
    heroEndFight_animation->setStartValue(QRect(Hero->x() + 30, Hero->y() - 30, Hero->width(), Hero->height()));
    heroEndFight_animation->setEndValue(QRect(Hero->x(), Hero->y(), Hero->width(), Hero->height()));

    heroFight_animation = new QSequentialAnimationGroup;
    heroFight_animation->addAnimation(heroGoFight_animation);
    heroFight_animation->addAnimation(heroEndFight_animation);

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

    connect(heroFight_animation, &QSequentialAnimationGroup::finished, this, &MainWindow::attack_next_part);
    connect(enemyFight_animation, &QSequentialAnimationGroup::finished, this, &MainWindow::activate_attack);

}

void MainWindow::get_next_ennemy(){

    qDebug() << "Getting next ennemy";
    actual_ennemy_position += 1;
    if (actual_ennemy_position >= ennemies.size()){

        victory();

    }
    else {

        actual_ennemy = ennemies.at(actual_ennemy_position);

        qDebug() << "Checking ennemy type";

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

        enemy_animation = new QPropertyAnimation(Enemy, "geometry");
        enemy_animation->setDuration(750);
        enemy_animation->setStartValue(QRect(Enemy->x(), Enemy->y(), Enemy->width(), Enemy->height()));
        enemy_animation->setEndValue(QRect(Enemy->x() - 500, Enemy->y(), Enemy->width(), Enemy->height()));
        enemy_animation->start();
        connect(enemy_animation, &QPropertyAnimation::finished, this, &MainWindow::activate_attack);

        Information->append("A " + QString::fromStdString(actual_ennemy->getName()) + " has spawn ! What do you want to do ?");
        Enemy_life->setMaximum(actual_ennemy->getLifePoint());
        Enemy_life->setValue(actual_ennemy->getLifePoint());
        setWindowTitle(QString::fromStdString("MePorg - Fight !                                                                                               " + hero->getName() + " vs " + actual_ennemy->getName()));

    }
}

void MainWindow::attack_next_part(){

    if (actual_ennemy->isDead()){

        enemy_die();

    }
    else{

        auto [name_attack,dmg] = actual_ennemy->enemyAttack(*hero);
        qDebug() << "Hero life before attack : " << hero->getLifePoint();
        hero->setLifePoint(dmg);
        qDebug() << "Hero life after attack : " << hero->getLifePoint();
        Information->append(QString::fromStdString(actual_ennemy->getName()) + " used " + name_attack);
        enemy_fight->play();
        enemyFight_animation->start();
        if (hero->getLifePoint() > 0){

            Hero_life->setValue(hero->getLifePoint());

        }
        else{

            Hero_life->setValue(0);

        }


    }

}

void MainWindow::check_hero_die(){

    qDebug() << "Checking if hero is dead";
    if (hero->isDead()){

        qDebug() << "Hero is dead";
        defeat();

    }
    qDebug() << "Hero is not dead";
}

void MainWindow::start_attack(){

    Attack1->setEnabled(false);
    Attack2->setEnabled(false);
    Attack4->setEnabled(false);
    Attack3->setEnabled(false);

    hero_fight->play();
    heroFight_animation->start();

}

void MainWindow::set_enemy_life(){

    if (actual_ennemy->getLifePoint() > 0){

        Enemy_life->setValue(actual_ennemy->getLifePoint());

    }
    else{

        Enemy_life->setValue(0);

    }

}

void MainWindow::attack1(){

    start_attack();

    qDebug() << "Attack 1 pressed";
    Information->append("You choose " + Attack1->text());
    qDebug() << "Ennemy life points before attack : " << actual_ennemy->getLifePoint();
    actual_ennemy->setLifePoint(hero->attack1(*actual_ennemy));
    set_enemy_life();
    qDebug() << "Ennemy life points after attack: " << actual_ennemy->getLifePoint();

}

void MainWindow::attack2(){

    start_attack();

    qDebug() << "Attack 2 pressed";
    Information->append("You choose " + Attack2->text());
    qDebug() << "Ennemy life points before attack : " << actual_ennemy->getLifePoint();
    int new_life_point = hero->attack2(*actual_ennemy);
    actual_ennemy->setLifePoint(new_life_point);
    set_enemy_life();
    qDebug() << "Ennemy life points after attack: " << actual_ennemy->getLifePoint();

}

void MainWindow::attack3(){

    start_attack();

    qDebug() << "Attack 3 pressed";
    Information->append("You choose " + Attack3->text());
    qDebug() << "Ennemy life points before attack : " << actual_ennemy->getLifePoint();
    int new_life_point = hero->attack3(*actual_ennemy);
    actual_ennemy->setLifePoint(new_life_point);
    set_enemy_life();
    qDebug() << "Ennemy life points after attack: " << actual_ennemy->getLifePoint();

}

void MainWindow::attack4(){

    start_attack();

    qDebug() << "Attack 4 pressed";
    Information->append("You choose " + Attack4->text());
    qDebug() << "Ennemy life points before attack : " << actual_ennemy->getLifePoint();
    int new_life_point = hero->attack4(*actual_ennemy);
    actual_ennemy->setLifePoint(new_life_point);
    set_enemy_life();
    qDebug() << "Ennemy life points after attack: " << actual_ennemy->getLifePoint();

}

void MainWindow::enemy_die(){

    qDebug() << "Ennemy is dead";
    Information->append(QString::fromStdString(actual_ennemy->getName()) + " has defited !");
    change_enemy();

}

void MainWindow::about_authors(){

    AboutWindow *w = new AboutWindow(this);
    w->show();

}

void MainWindow::info_items(){

    InfoItems *w = new InfoItems(this);
    w->show();

}

void MainWindow::version(){

    QMessageBox msg;
    msg.setWindowTitle("Version");
    msg.setText("Release 1.0");
    msg.setIcon(QMessageBox::Information);
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();

}

void MainWindow::exit(){

    QApplication::quit();

}

void MainWindow::reset(){

    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    delete this;

}

QString MainWindow::get_name(){

    QString text = QInputDialog::getText(this,"Type your name","Name ?                                                  ");
    if(text == ""){

        QMessageBox::warning(this, "No name typed", "You will be \"The Anonymous\"");
        text = QString("The Anonymous");

    }
    return text;

}

void MainWindow::victory(){

    musique->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/victory_sound.wav"));
    musique->play();
    QMessageBox msg;
    msg.setWindowTitle("Victory !");
    msg.setText("You win ! GG WP ! Feel free to try again, it may be harder next time :)");
    msg.setIcon(QMessageBox::Information);
    msg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    QPushButton *restart = new QPushButton();
    restart->setObjectName("button_restart");
    restart->setText("Restart");
    QPushButton *exit = new QPushButton();
    exit->setObjectName("button_exit");
    exit->setText("Exit");

    Game::setHighScore(actual_ennemy_position);

    connect(exit, &QPushButton::clicked, this, &MainWindow::exit);
    connect(restart, &QPushButton::clicked, this, &MainWindow::reset);

    msg.addButton(exit, QMessageBox::NoRole);
    msg.addButton(restart, QMessageBox::YesRole);
    msg.exec();

}

void MainWindow::defeat(){

    musique->setMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/ressources/death_sound.wav"));
    musique->play();
    QMessageBox msg;
    msg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    msg.setWindowTitle("Defeat...");
    msg.setText("You loose... Feel free to try again, next time will be yours !");
    msg.setIcon(QMessageBox::Information);

    QPushButton *restart = new QPushButton();
    restart->setObjectName("button_restart");
    restart->setText("Restart");
    QPushButton *exit = new QPushButton();
    exit->setObjectName("button_exit");
    exit->setText("Exit");

    Game::setHighScore(actual_ennemy_position);

    connect(exit, &QPushButton::clicked, this, &MainWindow::exit);
    connect(restart, &QPushButton::clicked, this, &MainWindow::reset);

    msg.addButton(exit, QMessageBox::NoRole);
    msg.addButton(restart, QMessageBox::YesRole);
    msg.exec();

}

QString MainWindow::get_job(){

    QMessageBox job;
    QString string;
    job.setWindowTitle("Job selection");
    job.setText("Select your job");
    QAbstractButton *Worker = job.addButton(tr("Worker"), QMessageBox::YesRole);
    QAbstractButton *Teacher = job.addButton(tr("Teacher"), QMessageBox::YesRole);
    QAbstractButton *Healer = job.addButton(tr("Healer"), QMessageBox::YesRole);
    job.exec();
    if (job.clickedButton() == Worker){

        string = "Worker";

    }
    else if (job.clickedButton() == Teacher){

        string = "Teacher";

    }
    else if (job.clickedButton() == Healer){

        string = "Healer";

    }

    return string;

}

void MainWindow::change_enemy(){

    enemy_animation = new QPropertyAnimation(Enemy, "geometry");
    enemy_animation->setDuration(750);
    enemy_animation->setStartValue(QRect(Enemy->x(), Enemy->y(), Enemy->width(), Enemy->height()));
    enemy_animation->setEndValue(QRect(Enemy->x() + 500, Enemy->y(), Enemy->width(), Enemy->height()));
    enemy_animation->start();
    connect(enemy_animation, &QPropertyAnimation::finished, this, &MainWindow::show_enemy_item);

}

void MainWindow::activate_attack(){

    Attack1->setEnabled(true);
    Attack2->setEnabled(true);
    Attack4->setEnabled(true);
    Attack3->setEnabled(true);

}

void MainWindow::show_enemy_item(){

    qDebug() << "Nombre d'items de " << actual_ennemy->getType() << " : " << actual_ennemy->getItems().getNumberItems();

    if (actual_ennemy->getItems().getNumberItems() == 0){

        get_next_ennemy();

    }
    else {

        ItemButton *button;
        QMessageBox msg;
        msg.setWindowTitle("Enemy carried item");
        msg.setText("What item do you want to keep ?");
        msg.setIcon(QMessageBox::Information);
        msg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        Item currentItem;

        for (int i = 0; i < actual_ennemy->getItems().getNumberItems(); i++){

            currentItem = actual_ennemy->getItems().getItem(i);
            button = new ItemButton(&currentItem, this);
            button->setObjectName(QString::fromStdString(actual_ennemy->getItems().getItem(i).getName()));
            button->setText(QString::fromStdString(actual_ennemy->getItems().getItem(i).getName()));
            button->setToolTip("This item gives you " + QString::number(actual_ennemy->getItems().getItem(i).getAttackPoint()) + " attack points, " + QString::number(actual_ennemy->getItems().getItem(i).getBrainPoint()) + " brain points, " + QString::number(actual_ennemy->getItems().getItem(i).getStrengthPoint()) + " strength points and " + QString::number(actual_ennemy->getItems().getItem(i).getLifePoint()) + " life points.");
            
            connect(button, SIGNAL(clicked(Item*)), this, SLOT(new_item(Item*)));
            msg.addButton(button, QMessageBox::YesRole);

        }

        button = new ItemButton(NULL, this);
        button->setObjectName("None");
        button->setText("None");
        connect(button, SIGNAL(clicked(Item*)), this, SLOT(new_item(Item*)));
        msg.addButton(button, QMessageBox::NoRole);
        msg.exec();

    }

}

void MainWindow::new_item(Item *new_item){

    if (new_item == nullptr){

        qDebug() << "None item was taken";
        get_next_ennemy();

    }
    else{

        *hero + *new_item;
        qDebug() << QString::fromStdString(new_item->getName()) << " added to your backpack.";
        get_next_ennemy();

    }

}

void MainWindow::new_item(){
}

void MainWindow::reset_high_score(){

    Game::setHighScore(0);
    reset();

}
