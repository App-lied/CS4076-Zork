#ifndef ITEM_H
#define ITEM_H

#include "gameobject.h"

class Item: public GameObject
{
public:
    friend bool operator==(const Item&, const Item&);
    Item()= default;
    Item(const QString &);

    //ASSESSMENT CRITERIA
    //copy constructor
    Item(const Item &i1) {mName = i1.mName; mFlag = i1.mFlag; mCollectable = i1.mCollectable; mDialogue = i1.mDialogue;};
    ~Item();

    bool isCollectable() { return mCollectable; };

    void read(const QJsonObject &json);

private:
    bool mCollectable;

    friend class Room;
};

#endif // ITEM_H
