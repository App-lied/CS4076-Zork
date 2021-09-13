#ifndef FILEMANAGE_H
#define FILEMANAGE_H

#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

#include "room.h"

class FileManage{
public:
    static bool loadgame(QList<Room> & gameRooms){
        QFile loadFile(QStringLiteral(":/data/gamedata.json"));

        if (!loadFile.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open save file.");
            return false;
        }

        QByteArray saveData = loadFile.readAll();

        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        FileManage::read(loadDoc.object(), gameRooms);

        return true;
    };

    static void read(const QJsonObject &json, QList<Room> & gameRooms){

        if (json.contains("rooms") && json["rooms"].isArray()) {
            QJsonArray levelArray = json["rooms"].toArray();
            gameRooms.clear();
            gameRooms.reserve(levelArray.size());
            for (int levelIndex = 0; levelIndex < levelArray.size(); ++levelIndex) {
                QJsonObject levelObject = levelArray[levelIndex].toObject();
                Room room;
                room.read(levelObject);
                gameRooms.append(room);
            }
        }

    };
};

#endif // FILEMANAGE_H
