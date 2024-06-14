/**
 * @file Player.h
 * @brief Defines the Player class which handles player actions and interactions within the game.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <vector>

#include "pokemon.h"

/**
 * @class Player
 * @brief The Player class represents the player character in the game.
 *
 * This class is responsible for managing player input, movement, and interactions
 * within the game scene, including collision detection and response.
 */
class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    /**
     * @brief Constructs a Player object with an optional parent item.
     * @param parent The parent QGraphicsItem, default is nullptr.
     */
    Player(QGraphicsItem *parent = nullptr);

    /**
     * @brief Destructor for the Player class.
     */
    ~Player();

    /**
     * @brief Retrieves the player's team of Pokémon.
     * @return A constant reference to a vector of pointers to Pokémon.
     */
    std::vector<Pokemon*> getTeam() const;

    /**
     * @brief Sets the player's team of Pokémon.
     * @param team The vector of Pokémon pointers to set.
     */
    void setTeam(vector<Pokemon*>);

    /**
     * @brief Handles key press events for player movement.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief Stops the player's movement.
     */
    void stopMoving();

    /**
     * @brief Adds a Pokémon to the player's team.
     * @param pokemon Pointer to the Pokémon to add.
     */
    void addPokemon(Pokemon *pokemon);

    /**
     * @brief Removes a Pokémon from the player's team.
     * @param pokemon Pointer to the Pokémon to remove.
     */
    void removePokemon(Pokemon *pokemon);

    /**
     * @brief Increments the player's win count.
     */
    void incrementWinCount();

    /**
     * @brief Retrieves the player's level.
     * @return The level of the player.
     */
    float getItsLevel() const;

    /**
     * @brief Sets the player's level.
     * @param newItsLevel The new level to set.
     */
    void setItsLevel(float newItsLevel);

    /**
     * @brief Retrieves the player's win count.
     * @return The number of battles won by the player.
     */
    int getWinCount() const;

    /**
     * @brief Sets the player's win count.
     * @param newWinCount The new win count to set.
     */
    void setWinCount(int newWinCount);

    /**
     * @brief Retrieves whether the player can move or not
     * @return Boolean indicating if the player can move or not.
     */
    bool getCanMove() const;

    /**
     * @brief Sets the player's ability to move.
     * @param newCanMove Boolean indicating if the player can move.
     */
    void setCanMove(bool newCanMove);

    /**
     * @brief Checks if the player's team is complete.
     * @return True if the team is complete, false otherwise.
     */
    bool getCompleteTeam() const;

    /**
     * @brief Sets the completeness of the player's team.
     * @param newCompleteTeam Boolean indicating if the team is complete.
     */
    void setCompleteTeam(bool newCompleteTeam);

private:
    std::vector<Pokemon*> itsTeam;  ///< The player's team of Pokémon.
    QTimer *movementTimer;          ///< Timer for handling continuous movement.
    QSet<int> activeKeys;           ///< Set of currently pressed keys.
    bool completeTeam = false;      ///< Flag indicating if the player's team is complete.
    bool canMove = true;            ///< Flag indicating whether the player can move.
    float scale = 1.8;              ///< Scale factor for the player's graphical representation.
    float itsLevel = 1.0;           ///< The player's movement speed.
    int winCount = 0;               ///< The number of battles won by the player.

    /**
     * @brief Checks for collisions at the new position.
     * @param newPos The new position to check for collisions.
     * @return True if there is a collision, false otherwise.
     */
    bool checkCollision(QPointF newPos);

    /**
     * @brief Initiates movement in a specific direction.
     */
    void startMoving();

    /**
     * @brief Updates the player's sprite based on the direction.
     * @param direction The direction in which the player is moving.
     */
    void updateSprite(const QString &direction);

protected:
    /**
     * @brief Handles key release events to stop player movement.
     * @param event The key event.
     */
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    /**
     * @brief Moves the player based on the currently pressed key.
     */
    void move();

signals:
    /**
     * @brief Signal emitted when the player encounters combat conditions.
     */
    void startEncounterCombat();

    /**
     * @brief Signal emitted when the player encounters a boss.
     */
    void startEncouterBoss();

    /**
     * @brief Signal emitted when the player encounters a sign.
     */
    void signEncounter(int x, int y);
};

#endif // PLAYER_H
