/**
 * @file GameOverHUD.h
 * @author Paulin Paul Achile Lilian
 * @brief Defines the GameOverHUD class, which displays the game over screen in a graphical format.
 */

#ifndef GAMEOVERHUD_H
#define GAMEOVERHUD_H

#include <QGraphicsScene>

/**
 * @class GameOverHUD
 * @brief A graphical scene representing the game over screen.
 *
 * This class manages the display elements for when the game concludes, showing a graphical game over screen.
 */
class GameOverHUD : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a GameOverHUD object.
     * @param parent The parent QObject, default is nullptr.
     */
    GameOverHUD(QObject *parent = nullptr);
};

#endif // GAMEOVERHUD_H
