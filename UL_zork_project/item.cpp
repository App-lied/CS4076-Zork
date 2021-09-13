#include <QJsonArray>

#include "item.h"

//ASSESSMENT CRITERIA
//overload the == operator for easier comparison with functions from containers like QList
bool operator==(const Item& lhs, const Item& rhs) {
    return(lhs.mName.compare(rhs.mName) == 0);
}

Item::Item(const QString &name) {
    mName = name;
}

Item::~Item() {}
void Item::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if(json.contains("collectable") && json["collectable"].isBool())
        mCollectable = json["collectable"].toBool();

    if (json.contains("dialogue") && json["dialogue"].isArray()) {
        QJsonArray dialogueArray = json["dialogue"].toArray();

        for (int dialogueIndex = 0; dialogueIndex < dialogueArray.size(); ++dialogueIndex) {
            Dialogue d = Dialogue(dialogueArray[dialogueIndex].toString());
            mDialogue[dialogueIndex + 1] = d;
        }
    }

    mFlag = 1;

}
