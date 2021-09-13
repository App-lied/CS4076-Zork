#include <QJsonArray>
#include "room.h"

//ASSESSMENT CRITERIA
//overload the == operator for easier comparison with functions from containers like QList
bool operator==(const Room& lhs, const Room& rhs) {
    return(lhs.mName.compare(rhs.mName) == 0);
}

Room::Room() {

}

//ASSESSMENT CRITERIA
//use of initialiser list
Room::Room(const QString &name):mName(name) {}

QString Room::name() const {
    return mName;
}
QStringList Room::itemNames() {
    QStringList names;
    QList<Item>::iterator i;
    for(i = mItems.begin(); i != mItems.end(); ++i)
        names.append((*i).mName);

    return names;
}
QStringList Room::npcNames() {
    QStringList names;
    QList<NPC>::iterator i;
    for(i = mNpcs.begin(); i != mNpcs.end(); ++i)
        names.append((*i).mName);

    return names;
}

Dialogue Room::currentDialogue() {
    return mDialogue[mFlag];
}

Item* Room::findItem(const QString &name) {
    Item temp = Item(name);
    QList<Item>::iterator i;
    for(i = mItems.begin(); i != mItems.end(); ++i) {
        if(*i == temp) {
            return i;
        }
    }

    return NULL;
}

NPC* Room::findNpc(const QString &name) {
    NPC temp = NPC(name);
    QList<NPC>::iterator i;
    for(i = mNpcs.begin(); i != mNpcs.end(); ++i) {
        if(*i == temp) {
            return i;
        }
    }

    return NULL;
}

void Room::read(const QJsonObject &json) {
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if (json.contains("north"))
        mExits["north"] = json["north"].toString();
    else
        mExits["north"] = "NULL";

    if (json.contains("south"))
        mExits["south"] = json["south"].toString();
    else
        mExits["south"] = "NULL";

    if (json.contains("east"))
        mExits["east"] = json["east"].toString();
    else
        mExits["east"] = "NULL";

    if (json.contains("west"))
        mExits["west"] = json["west"].toString();
    else
        mExits["west"] = "NULL";

    if (json.contains("dialogue") && json["dialogue"].isArray()) {
        QJsonArray dialogueArray = json["dialogue"].toArray();

        for (int dialogueIndex = 0; dialogueIndex < dialogueArray.size(); ++dialogueIndex) {
            Dialogue d = Dialogue(dialogueArray[dialogueIndex].toString());
            mDialogue[dialogueIndex + 1] = d;
        }
    }
    mFlag = 1;


    if (json.contains("npcs") && json["npcs"].isArray()) {
        QJsonArray npcArray = json["npcs"].toArray();
        mNpcs.clear();
        mNpcs.reserve(npcArray.size());
        for (int npcIndex = 0; npcIndex < npcArray.size(); ++npcIndex) {
            QJsonObject npcObject = npcArray[npcIndex].toObject();
            NPC npc;
            npc.read(npcObject);
            mNpcs.append(npc);
        }
    }


    if (json.contains("items") && json["items"].isArray()) {
        QJsonArray itemArray = json["items"].toArray();
        mItems.clear();
        mItems.reserve(itemArray.size());
        for (int itemIndex = 0; itemIndex < itemArray.size(); ++itemIndex) {
            QJsonObject itemObject = itemArray[itemIndex].toObject();
            Item item;
            item.read(itemObject);
            mItems.append(item);
        }
    }
}
