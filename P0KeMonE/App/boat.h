#ifndef BOAT_H
#define BOAT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPropertyAnimation>
#include "player.h"

class Boat : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    /**
     * @brief Constructor for the Boat class.
     * @param parent Optional parent item, defaults to nullptr.
     */
    Boat(QGraphicsItem *parent = nullptr);

    /**
     * @brief Starts the journey of the boat with the player.
     * @param player Pointer to the player object.
     */
    void startJourney(Player *player);

    /**
     * @brief Gets the journey status.
     * @return True if the journey is in progress, otherwise false.
     */
    bool getIsStartJourney();

private:
    Player *player; ///< Pointer to the player object
    QPointF startPoint; ///< Start point of the boat
    QPointF islandPoint1; ///< First island point in the middle of the lake
    QPointF islandPoint2; ///< Second island point in the middle of the lake
    QPointF endPoint; ///< End point of the journey
    QPropertyAnimation *animation; ///< Animation for the boat movement
    bool isStartJourney; ///< Indicates if the journey is in progress

    /**
     * @brief Updates the player's position during the journey.
     * @param value The new position value from the animation.
     */
    void updatePlayerPosition(const QVariant &value);

    /**
     * @brief Handles the completion of the journey.
     */
    void onJourneyFinished();
};

#endif // BOAT_H
