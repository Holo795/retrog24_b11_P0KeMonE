#include "mainhud.h"
#include <QFont>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>


MainHUD::MainHUD(QObject *parent) : QGraphicsScene(parent)
{
    setObjectName("mainMenu");

    // Charger et positionner l'image du titre
    QGraphicsPixmapItem* titleImage = new QGraphicsPixmapItem(QPixmap(":/menu/main_menu/logo_menu.png"));
    titleImage->setPos(150, 0);
    titleImage->setFlag(QGraphicsItem::ItemIsFocusable);
    titleImage->setFocus();

    // Charger et positionner l'image du personnage
    QGraphicsPixmapItem* characterImage = new QGraphicsPixmapItem(QPixmap(":/menu/main_menu/player_menu.png"));
    characterImage->setPos(220, 100);

    // Créer et positionner le texte d'invite
    QGraphicsTextItem* promptText = new QGraphicsTextItem("Press space to play");
    QFont promptFont("Arial", 24);
    promptFont.setUnderline(true);
    promptText->setFont(promptFont);
    promptText->setDefaultTextColor(Qt::black);
    promptText->setPos(250, 150);

    // Créer et positionner l'étiquette de production
    QGraphicsTextItem* tag = new QGraphicsTextItem("@ QTeam Production 2024");
    QFont tagFont("Arial", 16);
    tag->setFont(tagFont);
    tag->setDefaultTextColor(Qt::black);
    tag->setPos(260, 500);

    addItem(titleImage);
    addItem(promptText);
    addItem(characterImage);
    addItem(tag);
}




