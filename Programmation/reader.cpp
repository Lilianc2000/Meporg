#include "reader.h"

Reader::Reader(){

}

QJsonDocument Reader::readDataJson(){
    // The path of the file with the data
    QString path = qApp->applicationDirPath() + "/ressources/data.json";

    // data will store all the data in the file
    QByteArray data;

    // We try to open the file
    QFile inFile(path);
    // Check if the opening was successful
    if (!inFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        //
        throw QString("FATAL ERROR : The file \"data.json\" cannot be oppened, check your installation ! ");
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
