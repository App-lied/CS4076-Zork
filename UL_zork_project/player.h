#ifndef PLAYER_H
#define PLAYER_H

#include <QList>
#include "item.h"
class Player
{
public:
    Player();

    QStringList itemNames();

    void addItem(Item &);

private:
    QList<Item> mHeldItems;
};

#endif // PLAYER_H
