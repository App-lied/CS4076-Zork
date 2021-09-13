#include "dialogue.h"

Dialogue::Dialogue()
{

}

//constructs a new Dialogue object from a passed String
Dialogue::Dialogue(const QString &text)
{
    mText = text.split("/");
    mCurrentPosition = 0;
}

//Returns the text at the current position of the dialogue
QString Dialogue::currentText() {
    return mText.at(mCurrentPosition);
}

int Dialogue::currentPosition() {
    return mCurrentPosition;
}

//Advances the dialogue by 1 to the next position in the text
void Dialogue::advancePosition() {
    mCurrentPosition++;
}

//Checks if current position in the dialogue is the last
bool Dialogue::isLastText() {
    return (mCurrentPosition < mText.size()-1 ? false : true);
}
