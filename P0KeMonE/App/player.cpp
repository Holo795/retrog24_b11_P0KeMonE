#include "player.h"
#include <QGraphicsItem>

Player::Player(int x, int y) {}

void Player::move(int dX, int dY)
{

    QGraphicsRectItem *player = new QGraphicsRectItem(itsX, itsY, 16, 16);
    if(dX == 1 && dY == 0)
    {
        player->setPos(itsX += 1, itsY);
    }
    else if (dX == -1 && dY == 0)
    {
        player->setPos(itsX += -1, itsY);
    }
    else if (dX == 0 && dY == 1)
    {
        player->setPos(itsX, itsY += 1);
    }
    else if (dX == 0 && dY == -1)
    {
        player->setPos(itsX, itsY += -1);
    }

}

void Player::updateSprite(int dX, int dY)
{

}
