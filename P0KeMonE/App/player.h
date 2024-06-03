#ifndef PLAYER_H
#define PLAYER_H

#include <QPixmap>
#include <QGraphicsRectItem>

/**
 * @class Player
 * @brief The Player class represents a player character in a graphics scene.
 *
 * The Player class is a graphical item that can move within a scene.
 * It keeps track of its position, movement direction, and level.
 */
class Player : public QGraphicsRectItem
{
private:
    float itsLevel;  ///< The current level of the player.
    int itsDx;       ///< The direction of the player's movement along the x-axis.
    int itsDy;       ///< The direction of the player's movement along the y-axis.        ///< The current y position of the player.

public:
    /**
     * @brief Constructs a Player object at a given position.
     *
     * @param x The initial x position of the player.
     * @param y The initial y position of the player.
     */
    Player(int x, int y);

    /**
     * @brief Moves the player in a specified direction.
     *
     * @param dX The direction to move the player along the x-axis.
     * @param dY The direction to move the player along the y-axis.
     */
    void move(int dX, int dY);

    /**
     * @brief Updates the player's sprite based on direction.
     *
     * This function updates the player's graphical representation
     * depending on the direction of movement.
     *
     * @param dX The direction of the player's movement along the x-axis.
     * @param dY The direction of the player's movement along the y-axis.
     */
    void updateSprite(int dX, int dY);

    // Getters for private members
    float getLevel() const;
    int getDirectionX() const;
    int getDirectionY() const;
};

#endif // PLAYER_H

