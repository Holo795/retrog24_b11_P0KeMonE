#include "gameoverhud.h"
#include "QtWidgets/qgraphicsitem.h"

GameOverHUD::GameOverHUD(QObject *parent) : QGraphicsScene(parent)
{
    QImage backgroundImage(":/battleHUD/naafvpduf2861.png");

    // Redimensionner l'image
    QImage scaledImage = backgroundImage.scaled(480, 320, Qt::KeepAspectRatio);

    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(QPixmap::fromImage(scaledImage));
    backgroundItem->setPos(0, 0);

    // Ajouter l'élément redimensionné à la scène
    addItem(backgroundItem);
}

