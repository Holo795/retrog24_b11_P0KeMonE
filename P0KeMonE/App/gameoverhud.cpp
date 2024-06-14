#include "gameoverhud.h"
#include "QtWidgets/qgraphicsitem.h"

GameOverHUD::GameOverHUD(QObject *parent) : QGraphicsScene(parent)
{
    setObjectName("GameOverHUD");
    QImage backgroundImage(":/hud/battlehud_assets/game_over_bg.png");

    QImage scaledImage = backgroundImage.scaled(480, 320, Qt::KeepAspectRatio);

    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(QPixmap::fromImage(scaledImage));
    backgroundItem->setPos(0, 0);

    QGraphicsTextItem *replayText = new QGraphicsTextItem("PRESS SPACE TO REPLAY !");
    replayText->setDefaultTextColor(Qt::white);
    replayText->setFont(QFont("Arial", 12, QFont::Bold));
    replayText->setPos(140, 260);
    replayText->setZValue(3);

    setBackgroundBrush(QBrush(QColor(31, 31, 31)));

    addItem(replayText);
    addItem(backgroundItem);
}
