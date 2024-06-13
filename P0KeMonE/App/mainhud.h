/**
 * @file MainHUD.h
 * @author Paulin Paul Achile Lilian
 * @brief Defines the MainHUD class that handles the main menu interface for a game.
 */

#ifndef MAINHUD_H
#define MAINHUD_H

#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>

/**
 * @class MainHUD
 * @brief A graphical scene representing the main menu of the game.
 *
 * This class is responsible for displaying the main menu elements, including the title,
 * character images, and user prompts.
 */
class MainHUD : public QGraphicsScene
{
public:
    /**
     * @brief Constructs a MainHUD object.
     * @param parent The parent QObject, default is nullptr.
     */
    MainHUD(QObject *parent = nullptr);
};

#endif // MAINHUD_H
