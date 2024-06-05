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
#include <QTimer>

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
    /**
     * @brief Handles key press events for player movement.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

    void addPokemon(Pokemon *pokemon);

private:
    float scale = 1.8; ///< The scale factor for the player.

    std::vector<Pokemon*> itsTeam;

    /**
     * @brief Checks for collisions at the new position.
     * @param newPos The new position to check for collisions.
     * @return true if there is a collision, false otherwise.
     */
    bool checkCollision(QPointF newPos);

    QTimer *movementTimer; ///< Timer for handling continuous movement.
    int currentKey; ///< The currently pressed key.


public slots:
    /**
     * @brief Moves the player based on the currently pressed key.
     */
    void move();

    /**
     * @brief Starts moving the player in the direction of the specified key.
     * @param key The key representing the direction.
     */
    void startMoving(int key);

    /**
     * @brief Stops moving the player.
     */
    void stopMoving();


signals:
    /**
     * @brief Signal emitted when the player enter in grass to start pokemon combat.
     */
    void startEncounterCombat();

};

#endif // PLAYER_H
