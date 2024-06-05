#include "gameoverhud.h"
#include "QtWidgets/qgraphicsitem.h"

GameOverHUD::GameOverHUD(QObject *parent) : QGraphicsScene(parent)
{
    // Load and add the background image
    QImage backgroundImage(":/gameover/assets/gameover.png");
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(QPixmap::fromImage(backgroundImage));
    backgroundItem->setPos(0, 0);
    addItem(backgroundItem);

}
