#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <QStringList>

class Dialogue
{
public:
    Dialogue();
    Dialogue(const QString &);

    QString currentText();
    int currentPosition();
    void advancePosition();
    bool isLastText();

private:
    QStringList mText;
    int mCurrentPosition;
};

#endif // DIALOGUE_H
