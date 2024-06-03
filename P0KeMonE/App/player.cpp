#include "player.h"
#include <QGraphicsItem>
#include <QColor>
#include <QBrush>

Player::Player(int x, int y)
    : QGraphicsRectItem(x, y, 16, 16), itsLevel(1.0),  // Initialize itsLevel to 1.0 (assuming level starts at 1)
    itsDx(0),       // Initialize direction x to 0
    itsDy(0)       // Initialize direction y to 0
{
    // Set the initial position of the player
    setBrush(Qt::blue);    // Initial color of the player
    setZValue(2);
}
void Player::move(int dX, int dY)
{
    if(dX == 1 && dY == 0)
    {
        setPos(x() + 1, y());
    }
    else if (dX == -1 && dY == 0)
    {
        setPos(x() -1, y());
    }
    else if (dX == 0 && dY == 1)
    {
        setPos(x(), y() + 1);
    }
    else if (dX == 0 && dY == -1)
    {
        setPos(x(), y() -1);
    }
    updateSprite(dX, dY);

}

void Player::updateSprite(int dX, int dY)
{
    if(dX == 1 && dY == 0)
    {
        setBrush(Qt::green);
    }
    else if (dX == -1 && dY == 0)
    {
        setBrush(Qt::red);
    }
    else if (dX == 0 && dY == 1)
    {
        setBrush(Qt::black);
    }
    else if (dX == 0 && dY == -1)
    {
        setBrush(Qt::blue);
    }
}

// Getters for private members
float Player::getLevel() const {
    return itsLevel;
}

int Player::getDirectionX() const {
    return itsDx;
}

int Player::getDirectionY() const {
    return itsDy;
}

