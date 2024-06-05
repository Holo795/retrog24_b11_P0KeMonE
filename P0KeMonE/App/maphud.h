/**
 * @file MapHUD.h
 * @brief Defines the MapHUD class that handles the map interface for the game.
 */

#ifndef MAPHUD_H
#define MAPHUD_H

#include <QGraphicsScene>
#include <QKeyEvent>

#include "player.h"
#include "model.h"

/**
 * @class MapHUD
 * @brief A graphical scene representing the game map.
 *
 * This class is responsible for displaying the map elements and managing interactions,
 * such as player movement and interactions with the environment.
 */
class MapHUD : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a MapHUD object with a reference to the game model.
     * @param model Pointer to the game model used for obtaining map data.
     * @param parent Optional parent QObject, default is nullptr.
     */
    MapHUD(Model *model, QObject *parent = nullptr);

    /**
     * @brief Destructor for the MapHUD.
     */
    ~MapHUD();

    /**
     * @brief Draws the game map based on the data from the model.
     */
    void drawMap();

    /**
     * @brief Retrieves a pointer to the player object.
     * @return Pointer to the player.
     */
    Player *getPlayer();

private:
    Model *model; ///< Pointer to the model.
    Player *player; ///< Pointer to the player.

protected:
    /**
     * @brief Handles key press events for player movement and interactions.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAPHUD_H
