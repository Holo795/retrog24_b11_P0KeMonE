#include "mainhud.h"

/**
 * Constructor for the MainHUD class.
 * Initializes the main menu scene with graphical elements.
 */
MainHUD::MainHUD(QObject *parent) : QGraphicsScene(parent)
{
    setObjectName("mainMenu");

    QGraphicsPixmapItem* titleImage = new QGraphicsPixmapItem(QPixmap(":/hud/main_menu_assets/logo_menu.png"));
    titleImage->setPos(150, 0);
    titleImage->setFlag(QGraphicsItem::ItemIsFocusable);
    titleImage->setFocus();

    QGraphicsPixmapItem* characterImage = new QGraphicsPixmapItem(QPixmap(":/hud/main_menu_assets/player_menu.png"));
    characterImage->setPos(220, 100);

    QGraphicsTextItem* promptText = new QGraphicsTextItem("Press space to play");
    QFont promptFont("Minecraft", 24);
    promptFont.setUnderline(true);
    promptText->setFont(promptFont);
    promptText->setDefaultTextColor(Qt::black);
    promptText->setPos(250, 150);

    QGraphicsTextItem* tag = new QGraphicsTextItem("@ QTeam Production 2024");
    QFont tagFont("Minecraft", 16);
    tag->setFont(tagFont);
    tag->setDefaultTextColor(Qt::black);
    tag->setPos(260, 500);


    // Add all elements to the scene
    addItem(titleImage);
    addItem(promptText);
    addItem(characterImage);
    addItem(tag);
}
