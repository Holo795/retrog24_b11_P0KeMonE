/**
 * @file MapHUD.h
 * @author Paulin Paul Achile Lilian
 * @brief Defines the MapHUD class that handles the map interface for the game.
 */

#ifndef MAPHUD_H
#define MAPHUD_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QBitmap>
#include <random>

#include "player.h"
#include "model.h"
#include "boat.h"

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

    void showFirstScenario();
    void showSecondScenario();
    void endScenario();

    QGraphicsTextItem *getDialogTextItem();

    Boat *boat; ///< Pointer to the boat object.

private:
    Model *model;                                   ///< Pointer to the model.
    Player *player;                                 ///< Pointer to the player.
    std::mt19937 gen;                               ///< Mersenne Twister random number generator.
    std::uniform_int_distribution<> encounterDist;  ///< Distribution for random encounters.
    QGraphicsPixmapItem *bossItem;                  ///< Pointer to the boss item.
    QGraphicsPixmapItem *oldMenItem;                ///< Pointer to the old men item.
    QGraphicsPixmapItem *boxItem;                   ///< Pointer to the box item for dialogues.
    QGraphicsPixmapItem *ballsItem;                 ///< Pointer to the box item for dialogues.
    QGraphicsTextItem *textItem;                    ///< Pointer to the text item for dialogues.
    bool showSignMessage = true;                    ///< Flag to show sign message.

    /**
     * @brief Draws the grass layer of the map.
     * @param map The map data.
     */
    void drawGrassLayer(const std::vector<std::vector<int>>& map);

    /**
     * @brief Draws decorative and functional elements of the map.
     * @param map The map data.
     */
    void drawDecorativeElements(const std::vector<std::vector<int>>& map);

    /**
     * @brief Initializes the player object and adds it to the scene.
     */
    void initializePlayer();

    /**
     * @brief Handles interactions based on the tile type.
     * @param tileType The type of the tile the player is interacting with.
     */
    void handleTileInteraction(int tileType);

    /**
     * @brief Handles random encounters in specific map tiles.
     */
    void handleRandomEncounter();

private slots:
    /**
     * @brief Show sign message
     */
    void signMessage(int x, int y);

protected:
    /**
     * @brief Handles key press events for player movement and interactions.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief Manages the player's entrance into the launcher zone.
     * @param player Pointer to the player.
     */
    void enteringLauncher(Player *player);

};

#endif // MAPHUD_H
