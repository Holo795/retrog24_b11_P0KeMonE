#include "mainhud.h"
#include <QFont>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QFontDatabase>


/**
 * Constructor for the MainHUD class.
 * Initializes the main menu scene with graphical elements.
 */
MainHUD::MainHUD(QObject *parent) : QGraphicsScene(parent)
{
    setObjectName("mainMenu"); // Set a name for the scene for easy reference

    // Load and position the title image
    QGraphicsPixmapItem* titleImage = new QGraphicsPixmapItem(QPixmap(":/hud/main_menu_assets/logo_menu.png"));
    titleImage->setPos(150, 0); // Set position of the title
    titleImage->setFlag(QGraphicsItem::ItemIsFocusable);
    titleImage->setFocus(); // Set focus to make it interactable if needed

    // Load and position the character image
    QGraphicsPixmapItem* characterImage = new QGraphicsPixmapItem(QPixmap(":/hud/main_menu_assets/player_menu.png"));
    characterImage->setPos(220, 100); // Position the character image


    // Load custom font
    int fontId = QFontDatabase::addApplicationFont(":/hud/battlehud_assets/Minecraft.ttf");
    if (fontId == -1) {
        qDebug() << "Failed to load Minecraft font.";
    }
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    // Create and position the prompt text
    QGraphicsTextItem* promptText = new QGraphicsTextItem("Press space to play");
    QFont promptFont(fontFamily, 24);
    promptFont.setUnderline(true); // Underline the font for emphasis
    promptText->setFont(promptFont);
    promptText->setDefaultTextColor(Qt::black);
    promptText->setPos(250, 150); // Position the text

    // Create and position the production tag
    QGraphicsTextItem* tag = new QGraphicsTextItem("@ QTeam Production 2024");
    QFont tagFont(fontFamily, 16);
    tag->setFont(tagFont);
    tag->setDefaultTextColor(Qt::black);
    tag->setPos(260, 500); // Position the production label at the bottom


    // Add all elements to the scene
    addItem(titleImage);
    addItem(promptText);
    addItem(characterImage);
    addItem(tag);
}
