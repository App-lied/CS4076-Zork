#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "room.h"
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void play();

private slots:
    void nextClicked();
    void directionClicked(const QString &);
    void interactClicked();
    void talkClicked();

private:
    Ui::MainWindow *ui;
    QSignalMapper *movementButtons;

    QList<Room> mRooms;
    Room* mCurrentRoom;
    Dialogue mCurrentDialogue;
    Player mPlayer;

    void toggleNonTextButtons(bool);
    void displayText();

    void setCurrentRoom(Room*);

    Room* findRoom(const QString &);
};
#endif // MAINWINDOW_H
