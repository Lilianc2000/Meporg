#include "reader.h"

Reader::Reader(){

}

QJsonDocument Reader::readDataJson(){
    // Read file
    QString path = qApp->applicationDirPath() + "/ressources/data.json";

    QByteArray data;

    QFile inFile(path);
    if (!inFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "Error reading the file";
    } else {
        qDebug() << "Fichier bien ouvert";
        data = inFile.readAll();
        inFile.close();
    }

    // Convert to QJsonDocument
    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        qDebug() << "Parse failed";
    } else {
        qDebug() << "Parse not failed";
    }

    return doc;
};
