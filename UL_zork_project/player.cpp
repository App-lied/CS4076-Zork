#include "player.h"

Player::Player()
{
    mHeldItems = QList<Item>();
}

QStringList Player::itemNames() {
    QStringList names;
    QList<Item>::iterator i;
    for(i = mHeldItems.begin(); i != mHeldItems.end(); ++i)
        names.append((*i).name());

    return names;
}

void Player::addItem(Item &i) {
    mHeldItems.append(i);
}
