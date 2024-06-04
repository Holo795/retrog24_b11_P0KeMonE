/**
 * @file player.h
 * @brief Defines the Player class which handles player actions and collisions.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QKeyEvent>
#include <vector>
#include "pokemon.h"

/**
 * @class Player
 * @brief The Player class represents a player character in the game.
 *
 * The Player class is responsible for handling player input and interactions
 * within the game scene, including movement and collision detection.
 */
class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    /**
     * @brief Constructs a Player object.
     * @param parent The parent QGraphicsItem, default is nullptr.
     */
    Player(QGraphicsItem *parent = nullptr);

    std::vector<Pokemon*> getTeam() const;

private:
    float scale = 1.8; ///< The scale factor for the player.

    std::vector<Pokemon*> itsTeam;

    /**
     * @brief Checks for collisions at the new position.
     * @param newPos The new position to check for collisions.
     * @return true if there is a collision, false otherwise.
     */
    bool checkCollision(QPointF newPos);

protected:
    /**
     * @brief Handles key press events for player movement.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PLAYER_H
