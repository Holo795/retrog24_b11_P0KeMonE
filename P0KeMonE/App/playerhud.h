/**
 * @file playerhud.h
 * @brief Definition of the PlayerHUD class.
 */

#ifndef PLAYERHUD_H
#define PLAYERHUD_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QProgressBar>
#include <QButtonGroup>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>

#include "pokemon.h"

/**
 * @class PlayerHUD
 * @brief The PlayerHUD class provides a heads-up display (HUD) for the player in the game.
 *
 * This class extends QGraphicsScene and is responsible for displaying the player's team of Pokémon,
 * their health, and handling the selection of Pokémon during gameplay.
 */
class PlayerHUD : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a PlayerHUD object.
     * @param parent The parent object.
     */
    PlayerHUD(QObject *parent = nullptr);

    /**
     * @brief Sets the Pokémon to be displayed in the HUD.
     * @param pokemons A vector of Pokémon pointers.
     * @param itsLevelPlayer The level of the player.
     */
    void setPokemons(const std::vector<Pokemon*>& pokemons, int itsLevelPlayer);

    /**
     * @brief Enables or disables the selection mode.
     * @param selectionMode If true, selection mode is enabled; otherwise, it is disabled.
     */
    void setSelectionMode(bool selectionMode);

    /**
     * @brief Updates the HUD display.
     */
    void updateHUD();

protected:
    /**
     * @brief Handles key press events.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event) override;

private:
    /**
     * @brief Adds a character to the HUD.
     * @param characterImage The image of the character.
     * @param currentHealth The current health of the character.
     * @param maxHealth The maximum health of the character.
     * @param xPos The x position of the character.
     * @param yPos The y position of the character.
     */
    void addCharacter(const QPixmap &characterImage, int currentHealth, int maxHealth, int xPos, int yPos, Pokemon *pokemon);

    /**
     * @brief Updates the position of the selection arrow.
     */
    void updateSelectionArrow();

    std::vector<Pokemon*> pokemons; ///< The player's Pokémon team.
    QList<QGraphicsPixmapItem*> characterItems; ///< The list of character images.
    QList<QGraphicsTextItem*> healthTextItems; ///< The list of health text items.
    QList<QGraphicsProxyWidget*> healthBars; ///< The list of health bars.
    QGraphicsPixmapItem *selectionArrow; ///< The selection arrow.
    bool selectionMode; ///< Indicates whether selection mode is enabled.
    int selectedIndex; ///< The index of the selected Pokémon.
    int itsLevelPlayer; ///< The level of the player.

signals:
    /**
     * @brief Signal emitted when a Pokémon is selected.
     * @param pokemon A pointer to the selected Pokémon.
     */
    void pokemonSelected(Pokemon *pokemon);
};

#endif // PLAYERHUD_H
