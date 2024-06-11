#include "gameoverhud.h"
#include <QGraphicsPixmapItem>

/**
 * @brief Constructor for the GameOverHUD class.
 * Initializes the game over screen with a background image.
 * @param parent The parent QObject, default is nullptr.
 */
GameOverHUD::GameOverHUD(QObject *parent) : QGraphicsScene(parent)
{
    setObjectName("GameOverHUD");

    // Load a background image for the game over screen
    QImage backgroundImage(":/hud/battlehud_assets/game_over_bg.png");

    // Resize the image to fit the desired dimensions while maintaining aspect ratio
    QImage scaledImage = backgroundImage.scaled(480, 320, Qt::KeepAspectRatio);

    // Create a pixmap item from the scaled image
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(QPixmap::fromImage(scaledImage));
    backgroundItem->setPos(0, 0); // Position the image at the origin of the scene

    // Add the scaled and positioned item to the scene
    addItem(backgroundItem);
}
