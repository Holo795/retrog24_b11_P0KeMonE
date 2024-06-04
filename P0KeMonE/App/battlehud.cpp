#include "battlehud.h"


#include <QFont>
#include <QImage>
#include <QPixmap>
#include <iostream>
#include "battle.h"

BattleHUD::BattleHUD(QGraphicsScene *scene) {
    this->scene = scene;

    scene->clear();

    background = new QGraphicsPixmapItem(QPixmap(":/battleHUD/battleHUD-background.png").scaled(480, 240));
    background->setPos(0, 0);
    scene->addItem(background);

    // Create and configure the attack button
    attackButton = new QPushButton();
    QPixmap buttonImage(":/battleHUD/fight_button.png.opdownload");
    attackButton->setIcon(QIcon(buttonImage));

    int buttonWidth = 105;
    int buttonHeight = 40;
    attackButton->setIconSize(QSize(buttonWidth, buttonHeight));
    attackButton->setFixedSize(buttonWidth, buttonHeight);
    attackButton->setGeometry(190, 250, buttonWidth, buttonHeight);
    scene->addWidget(attackButton);


}

void BattleHUD::displayOptions()
{

}

void BattleHUD::chooseOption(Move option)
{

}
