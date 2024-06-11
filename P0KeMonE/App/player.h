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
#include <vector>
#include <QTimer>
#include <QSet>
#include <QPointF>
#include "typeDef.h"
#include "pokemon.h"
#include "soundmanager.h"

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
     * @param newTeam A vector of pointers to Pokémon.
     */
    void setTeam(const std::vector<Pokemon*> &newTeam);

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
     * @brief Retrieves the player's current level.
     * @return The player's current level.
     */
    float getItsLevel() const;

    /**
     * @brief Sets the player's current level.
     * @param newItsLevel The new level to set.
     */
    void setItsLevel(float newItsLevel);

    /**
     * @brief Retrieves the player's win count.
     * @return The player's win count.
     */
    int getWinCount() const;

    /**
     * @brief Sets the player's win count.
     * @param newWinCount The new win count to set.
     */
    void setWinCount(int newWinCount);

    /**
     * @brief Increments the player's win count.
     */
    void incrementWinCount();

    /**
     * @brief Initiates movement in a specific direction.
     */
    void startMoving();

    /**
     * @brief Stops the player's movement.
     */
    void stopMoving();

    /**
     * @brief Handles key press events for player movement.
     * @param event The key event.
     */
    void handleKeyPress(QKeyEvent *event);

    /**
     * @brief Handles key release events to stop player movement.
     * @param event The key event.
     */
    void handleKeyRelease(QKeyEvent *event);


protected:
    /**
     * @brief Handles key press events for player movement.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Handles key release events to stop player movement.
     * @param event The key event.
     */
    void keyReleaseEvent(QKeyEvent *event) override;

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
     * @brief Signal emitted when the player encounters
     */
    void startEncouterOldMen();

    /**
     * @brief Signal emitted when the player face on sign
     */
    void signEncounter(int x, int y) const;


private:
    /**
     * @brief Checks for collisions at the new position.
     * @param newPos The new position to check for collisions.
     * @return true if there is a collision, false otherwise.
     */
    bool checkCollision(QPointF newPos) const;

    /**
     * @brief Updates the player's sprite based on the direction.
     * @param direction The direction in which the player is moving.
     */
    void updateSprite(const QString &direction);

    float scale = 1.8; ///< Scale factor for the player's graphical representation.
    std::vector<Pokemon*> itsTeam; ///< The player's team of Pokémon.
    QTimer *movementTimer; ///< Timer for handling continuous movement.
    QSet<int> activeKeys; ///< Set of currently pressed keys.
    float itsLevel = 1.0; ///< The player's current level.
    int winCount = 0; ///< The number of battles won by the player.
};

#endif // PLAYER_H
