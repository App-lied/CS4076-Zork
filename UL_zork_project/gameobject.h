#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>
#include <QJsonObject>
#include <QMap>

#include "dialogue.h"

//ASSESSMENT CRITERIA
//abstract class with a virtual function that is implemented in NPC and Item
class GameObject {
public:
    virtual ~GameObject() = 0;

    virtual void read(const QJsonObject &json) = 0;

    QString name() {return mName;};
    Dialogue currentDialogue() { return mDialogue[mFlag]; };
    int currentFlag() { return mFlag; };
    void setFlag(int i) { mFlag = i; };

//ASSESSMENT CRITERIA
//use of protected
protected:
    QString mName;

    //ASSESSMENT CRITERIA
    //using a bit field/structure to reduce the storage space for an object's flag value
    int mFlag : 5;

    QMap<int, Dialogue> mDialogue;

    friend class Room;
};

#endif // GAMEOBJECT_H
