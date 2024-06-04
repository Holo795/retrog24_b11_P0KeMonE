#ifndef BATTLEHUD_H
#define BATTLEHUD_H

#include "move.h"

#include <vector>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QObject>



/**
 * @class BattleHUD
 * @brief The BattleHUD class manages the display of battle options and actions in the game.
 *
 * The BattleHUD class handles the graphical user interface for battle actions, including
 * displaying options and handling user input for selecting moves.
 */
class BattleHUD
{
public:
    /**
     * @brief Constructs a BattleHUD object with a given scene.
     *
     * @param scene The QGraphicsScene where the HUD elements will be displayed.
     */
    BattleHUD(QGraphicsScene* scene);

    /**
     * @brief Displays the available attack options.
     *
     * This function sets up the graphical elements to show the player the possible moves they can make.
     */
    void displayOptions();

private:
    std::vector<Move> attackOptions;  ///< List of available attack options.

    QGraphicsScene *scene;            ///< Scene for displaying game elements.
    QGraphicsTextItem* move;          ///< Text item to display the current move.
    QPushButton* attackButton;        ///< Button to initiate an attack.
    QGraphicsPixmapItem *background;  ///< Background image for the battle HUD.
    QGraphicsPixmapItem *pokemon1Item;
    QGraphicsPixmapItem *pokemon2Item;
    QGraphicsTextItem* health1;
    QGraphicsTextItem* health2;


public slots:
    /**
     * @brief Slot function to handle attack button clicks.
     *
     * This function is triggered when the attack button is clicked and handles the attack action.
     */
    void attackButtonClicked();
};

#endif // BATTLEHUD_H
