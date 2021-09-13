#include <QJsonArray>

#include "npc.h"

//ASSESSMENT CRITERIA
//overload the == operator for easier comparison with functions from containers like QList
bool operator==(const NPC& lhs, const NPC& rhs) {
    return(lhs.mName.compare(rhs.mName) == 0);
}

NPC::NPC(const QString &name) {
    mName = name;
}

NPC::~NPC() {};

void NPC::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if (json.contains("dialogue") && json["dialogue"].isArray()) {
        QJsonArray dialogueArray = json["dialogue"].toArray();

        for (int dialogueIndex = 0; dialogueIndex < dialogueArray.size(); ++dialogueIndex) {
            Dialogue d = Dialogue(dialogueArray[dialogueIndex].toString());
            mDialogue[dialogueIndex + 1] = d;
        }
    }
    mFlag = 1;

}
