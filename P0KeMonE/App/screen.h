/**
 * @file screen.h
 * @brief Déclaration de la classe Screen pour gérer les écrans du jeu.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

/**
 * @class Screen
 * @brief La classe Screen gère les différents écrans du jeu, tels que le menu principal et l'écran de bataille.
 */
class Screen : public QGraphicsView {
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe Screen.
     * @param scene Pointeur vers la scène graphique utilisée pour afficher les éléments du jeu.
     */
    Screen(QGraphicsScene* scene);
    /**
     * @brief Affiche le menu principal.
     */
    void displayMainMenu();
    /**
     * @brief Affiche l'écran de bataille.
     */
    void displayBattleScreen();
    /**
     * @brief Met à jour l'écran.
     */
    void updateScreen();


protected:
    /**
     * @brief Gère les événements de pression de touche.
     * @param event Pointeur vers l'événement de pression de touche.
     */
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *scene;                 ///< Scène graphique pour afficher les éléments du jeu.
    QGraphicsPixmapItem *titleImage;       ///< Image du titre.
    QGraphicsTextItem *promptText;         ///< Texte d'invite pour démarrer le jeu.
    QGraphicsPixmapItem *characterImage;   ///< Image du personnage.
    QGraphicsTextItem *tag;                ///< Texte de l'étiquette de production.
};

#endif // SCREEN_H
