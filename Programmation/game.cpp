#include "game.h"

Game::Game(){
}

Entity* Game::createHero(std::string name,std::string class_type,std::string job){
    // Le hero qui sera renvoyé
    Entity* h;

    // On crée la classe Hero avec la bonne classe
    if (class_type == "Demon"){
        h = new HeroDemon(name,job);
    } else if (class_type == "Human"){
        h = new HeroHuman(name,job);
    } else if (class_type == "Wolf"){
        h = new HeroWolf(name,job);
    } else if (class_type == "Werewolf"){
        h = new HeroWerewolf(name,job);
    } else {
        throw QString("Error  : mauvaise entrée dans la fonction Game.createHero");
        h = NULL;
    }

    return h;

};

std::vector<Entity*> Game::createEnemies(int number_enemies){
    // Create a vector of enemies
    std::vector<Entity*> enemies;

    for (int i = 0; i < number_enemies; i++){
        // Random job generation
        int class_enemy = std::rand() % 4;

        if (class_enemy == 1){
            Entity* enemy = new EnemyDemon();
            enemies.push_back(enemy);

        } else if (class_enemy == 2) {
            Entity* enemy = new EnemyHuman();
            enemies.push_back(enemy);

        } else if (class_enemy == 3) {
            Entity* enemy = new EnemyWolf();
            enemies.push_back(enemy);

        } else if (class_enemy == 4) {
            Entity* enemy = new EnemyWerewolf();
            enemies.push_back(enemy);
        }
    }
    return enemies;

};


// Read the highscore
int Game::readHighScore(){
    QJsonDocument doc = Reader::readDataJson();
    return doc["highscore"].toInt();
};

// Set the highscore
void Game::setHighScore(int new_highscore){
    // Read the JSON file
    QJsonDocument doc = Reader::readDataJson();

    // Check if the new highscore is greater than the current one
    if (new_highscore > doc["highscore"].toInt()){
        // Change the JSON Object with the new high score
        QJsonObject root(doc.object());
        root["highscore"] = new_highscore;
        doc.setObject(root);

        // Open and write the file
        QString path = qApp->applicationDirPath() + "/ressources/data.json";
        QFile file(path);
        file.open(QIODevice::WriteOnly);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    }
};


void Game::resetHighScore(){
    // Read the JSON file
    QJsonDocument doc = Reader::readDataJson();

    // Check if the new highscore is greater than the current one
    // Change the JSON Object with the new high score
    QJsonObject root(doc.object());
    root["highscore"] = 0;
    doc.setObject(root);

    // Open and write the file
    QString path = qApp->applicationDirPath() + "/ressources/data.json";
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
};

void Game::generateErrorMessageBox(QString error){
    // On ouvre une QMessageBox affichant un message d'erreur
    QMessageBox msg;
    msg.setWindowTitle("Version");
    msg.setText(error);
    msg.setIcon(QMessageBox::Information);
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();
};
