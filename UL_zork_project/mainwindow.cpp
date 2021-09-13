#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filemanage.h"

//The constructor for main window
//attaches the NSEW buttons to a signal mapper, which links them all to the same slot
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    movementButtons = new QSignalMapper(this);
    connect(movementButtons, SIGNAL(mappedString(const QString &)), this, SLOT(directionClicked(const QString &)));

    movementButtons->setMapping(ui->northButton, "north");
    movementButtons->setMapping(ui->southButton, "south");
    movementButtons->setMapping(ui->eastButton, "east");
    movementButtons->setMapping(ui->westButton, "west");

    connect(ui->northButton, SIGNAL(clicked()), movementButtons, SLOT(map()));
    connect(ui->southButton, SIGNAL(clicked()), movementButtons, SLOT(map()));
    connect(ui->eastButton, SIGNAL(clicked()), movementButtons, SLOT(map()));
    connect(ui->westButton, SIGNAL(clicked()), movementButtons, SLOT(map()));

}

//ASSESSMENT CRITERIA
//destructor that deletes class' defined pointer for the current room
MainWindow::~MainWindow()
{
    delete ui;
    delete mCurrentRoom;
}

void MainWindow::play() {
    if(FileManage::loadgame(mRooms)) {
        mPlayer = Player();
        Room* start = findRoom("Train Station");
        setCurrentRoom(start);
    }
}

//this slot is called when the Next button beneath the dialogue window is clicked
void MainWindow::nextClicked() {
    mCurrentDialogue.advancePosition();
    displayText();
}

//this slot is called when one of the NSEW buttons is clicked
void MainWindow::directionClicked(const QString &dir) {
    if(mCurrentRoom->mExits[dir] != "NULL") {
        Room *nextRoom = findRoom(mCurrentRoom->mExits[dir]);
        setCurrentRoom(nextRoom);
    } else {
        ui->textBox->setText("No need to go this way.");
    }
}


//this slot is called when the interact button is clicked
void MainWindow::interactClicked() {
    QString selected = ui->itemList->currentItem()->text();

    Item* item = mCurrentRoom->findItem(selected);
    mCurrentDialogue = item->currentDialogue();

    ui->textBox->clear();
    displayText();

    if(item->isCollectable()){
        Item newItem = *item;
        mPlayer.addItem(newItem);
        mCurrentRoom->mItems.removeAll(*item);
        ui->itemList->clear();
        ui->itemList->addItems(mCurrentRoom->itemNames());
        ui->inventoryList->clear();
        ui->inventoryList->addItems(mPlayer.itemNames());
    }
}

//this slot is called when the talk button is clicked
void MainWindow::talkClicked() {
    QString selected = ui->npcList->currentItem()->text();

    NPC* npc = mCurrentRoom->findNpc(selected);
    mCurrentDialogue = npc->currentDialogue();

    ui->textBox->clear();
    displayText();
}

//this function disables all buttons but the Next button when a dialogue is active
void MainWindow::toggleNonTextButtons(bool b) {
    ui->advanceText->setEnabled(b);

    ui->interactButton->setEnabled(!b);
    ui->talkButton->setEnabled(!b);
    ui->northButton->setEnabled(!b);
    ui->southButton->setEnabled(!b);
    ui->eastButton->setEnabled(!b);
    ui->westButton->setEnabled(!b);
}

//this function displays the next part of the current dialogue into the text window
void MainWindow::displayText() {
    ui->textBox->append(mCurrentDialogue.currentText());

    if(mCurrentDialogue.currentPosition() == 0 && !mCurrentDialogue.isLastText()) {
        toggleNonTextButtons(true);
    } else if (mCurrentDialogue.currentPosition() != 0 && mCurrentDialogue.isLastText()) {
        toggleNonTextButtons(false);
    }
}

//this function changes the current room and updates all necessary UI elements
void MainWindow::setCurrentRoom(Room* nextRoom) {
    mCurrentRoom = nextRoom;

    ui->roomName->setText(mCurrentRoom->name());

    ui->itemList->clear();
    ui->itemList->addItems(mCurrentRoom->itemNames());

    ui->npcList->clear();
    ui->npcList->addItems(mCurrentRoom->npcNames());

    ui->northExit->setText(mCurrentRoom->mExits["north"] == "NULL" ? "X" : mCurrentRoom->mExits["north"]);
    ui->southExit->setText(mCurrentRoom->mExits["south"] == "NULL" ? "X" : mCurrentRoom->mExits["south"]);
    ui->eastExit->setText(mCurrentRoom->mExits["east"] == "NULL" ? "X" : mCurrentRoom->mExits["east"]);
    ui->westExit->setText(mCurrentRoom->mExits["west"] == "NULL" ? "X" : mCurrentRoom->mExits["west"]);

    mCurrentDialogue = mCurrentRoom->currentDialogue();
    ui->textBox->clear();
    displayText();
    if(mCurrentRoom->mFlag == 1) {
        mCurrentRoom->mFlag = 2;
    }
}

//this function searches for and returns a room based on the passed name
Room* MainWindow::findRoom(const QString &name) {
    Room temp = Room(name);
    QList<Room>::iterator i;
    for(i = mRooms.begin(); i != mRooms.end(); ++i) {
        if(*i == temp) {
            return i;
        }
    }

    return NULL;
}
