#include "boat.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>

Boat::Boat(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), player(nullptr), animation(new QPropertyAnimation(this, "pos")), isStartJourney(false)
{
    // Set the boat image
    setPixmap(QPixmap(":/map/map_assets/boat_left.png"));
    setZValue(2); // Ensure the boat is on top of other items

    startPoint = QPointF(32*18 - 2, 32*29); // Set the actual start coordinates
    islandPoint1 = QPointF(32*23 + 1, 32*27); // Set the actual island coordinates
    islandPoint2 = QPointF(32*23, 32*27); // Set the actual island coordinates
    endPoint = QPointF(32*31 + 2, 32*30); // Set the actual end point coordinates

    setPos(startPoint); // Set the initial position of the boat

    // Initialize the animation
    connect(animation, &QPropertyAnimation::valueChanged, this, &Boat::updatePlayerPosition);
    connect(animation, &QPropertyAnimation::finished, this, &Boat::onJourneyFinished);
}

void Boat::startJourney(Player *player)
{
    this->player = player;

    if (animation->state() == QPropertyAnimation::Running)
        return;

    isStartJourney = true;

    player->stopMoving();
    player->setCanMove(false);
    player->setVisible(false);

    animation->setDuration(3000); // Duration to reach the island
    animation->setStartValue(pos());

    QPointF endValue;

    if (pos() == startPoint)
        endValue = islandPoint1;
    else if (pos() == islandPoint1)
        endValue = endPoint;
    else if (pos() == endPoint)
        endValue = islandPoint2;
    else if (pos() == islandPoint2)
        endValue = startPoint;

    animation->setEndValue(endValue);
    animation->start();
}

void Boat::updatePlayerPosition(const QVariant &value)
{
    QPointF newPos = value.toPointF();
    player->setPos(newPos);
    setPos(newPos);
}

void Boat::onJourneyFinished()
{
    if (pos() == islandPoint1 || pos() == islandPoint2)
        player->setPos(pos() + QPointF(40, 40));
    else if (pos() == endPoint) {
        setPixmap(QPixmap(":/map/map_assets/boat_right.png"));
        player->setPos(pos() + QPointF(104, 0));
    } else if (pos() == startPoint) {
        setPixmap(QPixmap(":/map/map_assets/boat_left.png"));
        player->setPos(pos() + QPointF(-40, 0));
    }

    player->setVisible(true);
    player->setCanMove(true);
    player->stopMoving();
    player->setFocus();

    isStartJourney = false;
}

bool Boat::getIsStartJourney()
{
    return isStartJourney;
}
