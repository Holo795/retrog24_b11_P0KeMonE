/**
 * @file BattleHUD.h
 * @brief Defines the BattleHUD class, which handles the graphical user interface for battles in a Pokémon game.
 */

#ifndef BATTLEHUD_H
#define BATTLEHUD_H

#include <QGraphicsScene>
#include <QPushButton>

#include "pokemon.h"

/**
 * @class BattleHUD
 * @brief Represents the battle heads-up display (HUD) using Qt's QGraphicsScene.
 *
 * This class is responsible for displaying the battle interface, including Pokémon and their health,
 * and managing interactions through buttons.
 */
class BattleHUD : public QGraphicsScene {
    Q_OBJECT

public:
    /**
     * @brief Constructs a BattleHUD scene with an optional parent.
     * @param parent The parent QObject, default is nullptr.
     */
    BattleHUD(QObject *parent = nullptr);

    /**
     * @brief Retrieves the attack button.
     * @return A pointer to the QPushButton used for attacks.
     */
    QPushButton *getAttackButton();

    /**
     * @brief Updates the displayed Pokémon and their health on the HUD.
     * @param pk1 Pointer to the first Pokémon.
     * @param pk2 Pointer to the second Pokémon.
     */
    void setPokemon(Pokemon *pk1, Pokemon *pk2);

    /**
     * @brief Gets the first Pokémon shown in the HUD.
     * @return A constant pointer to the first Pokémon.
     */
    Pokemon *getPokemon1() const;

    /**
     * @brief Gets the second Pokémon shown in the HUD.
     * @return A constant pointer to the second Pokémon.
     */
    Pokemon *getPokemon2() const;

private:
    QPushButton *attackButton;           /**< Button used for initiating attacks. */
    Pokemon *pokemon1;                   /**< First Pokémon displayed on the HUD. */
    Pokemon *pokemon2;                   /**< Second Pokémon displayed on the HUD. */
    QGraphicsPixmapItem *pokemon1Item;   /**< Graphics item for the first Pokémon's image. */
    QGraphicsPixmapItem *pokemon2Item;   /**< Graphics item for the second Pokémon's image. */
    QGraphicsTextItem *health1;          /**< Text item for the first Pokémon's health. */
    QGraphicsTextItem *health2;          /**< Text item for the second Pokémon's health. */
};

#endif // BATTLEHUD_H
