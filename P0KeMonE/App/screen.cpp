/**
 * @file screen.cpp
 * @brief Implémentation de la classe Screen pour gérer les écrans du jeu.
 */

#include "screen.h"
#include <QFont>
#include <QImage>
#include <QPixmap>
#include <iostream>

/**
 * @brief Constructeur de la classe Screen.
 * @param scene Pointeur vers la scène graphique utilisée pour afficher les éléments du jeu.
 */
Screen::Screen(QGraphicsScene* scene) {

    this->scene = scene;

    // Charger et positionner l'image du titre
    titleImage = new QGraphicsPixmapItem(QPixmap(":/menu/main_menu/logo_menu.png"));
    titleImage-> setPos(150, 0);

    // Charger et positionner l'image du personnage
    characterImage = new QGraphicsPixmapItem(QPixmap(":/menu/main_menu/player_menu.png"));
    characterImage->setPos(220, 100);

    // Créer et positionner le texte d'invite
    promptText = new QGraphicsTextItem("Press any key to play");
    QFont promptFont("Arial", 24);
    promptFont.setUnderline(true);
    promptText->setFont(promptFont);
    promptText->setDefaultTextColor(Qt::black);
    promptText->setPos(250, 150);

    // Créer et positionner l'étiquette de production
    tag = new QGraphicsTextItem("@ QTeam Production 2024");
    QFont tagFont("Arial", 16);
    tag->setFont(tagFont);
    tag->setDefaultTextColor(Qt::black);
    tag->setPos(260, 500);
}

/**
 * @brief Affiche le menu principal.
 */
void Screen::displayMainMenu() {
    scene->clear();

    scene->addItem(titleImage);
    scene->addItem(promptText);
    scene->addItem(characterImage);
    scene->addItem(tag);

    updateScreen();
}

/**
 * @brief Affiche l'écran de bataille.
 */
void Screen::displayBattleScreen() {
    scene->clear();
    // Ajouter les éléments de l'écran de bataille à la scène
}

/**
 * @brief Met à jour l'écran.
 */
void Screen::updateScreen() {
    scene->update();
}

/**
 * @brief Gère les événements de pression de touche.
 * @param event Pointeur vers l'événement de pression de touche.
 */
void Screen::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        std::cout << "Enter key pressed" << std::endl;
        displayBattleScreen();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
