#ifndef ROOM_H
#define ROOM_H

#include <QList>

#include "npc.h"
#include "item.h"

class Room
{
public:
    friend bool operator==(const Room&, const Room&);
    Room();
    Room(const QString &);

    QString name() const;
    QStringList itemNames();
    QStringList npcNames();

    Dialogue currentDialogue();

    Item* findItem(const QString &);
    NPC* findNpc(const QString &);

    void read(const QJsonObject &json);
private:
    int mFlag;
    QString mName;
    QMap<int, Dialogue> mDialogue;
    QList<NPC> mNpcs;
    QList<Item> mItems;
    QMap<QString, QString> mExits;

    friend class MainWindow;
};

#endif // ROOM_H
