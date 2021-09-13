#ifndef NPC_H
#define NPC_H

#include "gameobject.h"

class NPC: public GameObject
{
public:
    friend bool operator==(const NPC&, const NPC&);
    NPC() = default;
    NPC(const QString &);
    ~NPC();

    void read(const QJsonObject &json);

};

#endif // NPC_H
