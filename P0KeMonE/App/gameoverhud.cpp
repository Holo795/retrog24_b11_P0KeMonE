#include "gameoverhud.h"
#include "QtWidgets/qgraphicsitem.h"

GameOverHUD::GameOverHUD(QObject *parent) : QGraphicsScene(parent)
{
    setObjectName("GameOverHUD");
    QImage backgroundImage(":/hud/battlehud_assets/game_over_bg.png");

    QImage scaledImage = backgroundImage.scaled(480, 320, Qt::KeepAspectRatio);

    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(QPixmap::fromImage(scaledImage));
    backgroundItem->setPos(0, 0);

    addItem(backgroundItem);
}
