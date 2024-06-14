/**
 * @file BattleHUD.h
 * @author Paulin Paul Achile Lilian
 * @brief Defines the BattleHUD class, which handles the graphical user interface for battles in a Pokémon game.
 */

#ifndef BATTLEHUD_H
#define BATTLEHUD_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemAnimation>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QProgressBar>
#include <QTimeLine>
#include <QTimer>
#include <QDebug>

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
     * @brief Destructor for the BattleHUD.
     */
    ~BattleHUD();

    /**
     * @brief Retrieves the attack button.
     * @return A pointer to the QPushButton used for attacks.
     */
    QPushButton *getAttackButton();

    /**
     * @brief Retrieves the pokemon button.
     * @return A pointer to the QPushButton used for changing pokemon.
     */
    QPushButton *getPokemonButton();

    /**
     * @brief Retrieves the run button.
     * @return A pointer to the QPushButton used for leaving the battle.
     */
    QPushButton *getRunButton();

    /**
     * @brief Updates the displayed Pokémon and their health on the HUD.
     * @param pk1 Pointer to the first Pokémon.
     * @param pk2 Pointer to the second Pokémon.
     */
    void setPokemon(Pokemon *pk1, Pokemon *pk2);

    /**
     * @brief Shakes the Pokémon's image on the HUD.
     * @param pk Pointer to the Pokémon to shake.
     */
    void shakePokemon(Pokemon *pk);

    /**
     * @brief Dashes the Pokémon's image on the HUD.
     * @param pk Pointer to the Pokémon to dash.
     */
    void frontDashPokemon(Pokemon *pk);

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

    /**
     * @brief Displays the available moves from pokemon 1 as buttons.
     */
    void displayMoves();

    /**
     * @brief Shows the fight menu with attack, pokemon, and run buttons.
     */
    void menuFight();

    /**
     * @brief Retrieves the move buttons group.
     * @return A pointer to the QButtonGroup for move buttons.
     */
    QButtonGroup *getMoveGroup() const;

    /**
     * @brief Retrieves the back button.
     * @return A pointer to the QPushButton used for going back.
     */
    QPushButton *getBackButton() const;

    /**
     * @brief Sets the text to display in the HUD.
     * @param text The text to display.
     */
    void setText(string text);

    /**
     * @brief Updates the health bars of the Pokémon.
     */
    void updateHealthBars();

    /**
     * @brief Adds a personal item to the HUD.
     * @param item Pointer to the QGraphicsPixmapItem to add.
     */
    void addPersonalItem(QGraphicsPixmapItem *item);

    /**
     * @brief Retrieves the old men's pixmap item.
     * @return A pointer to the QGraphicsPixmapItem representing the old men.
     */
    QGraphicsPixmapItem* getOldMenPixmap();

    /**
     * @brief Retrieves the boss's pixmap item.
     * @return A pointer to the QGraphicsPixmapItem representing the boss.
     */
    QGraphicsPixmapItem* getBossPixmap();

    /**
     * @brief Enables the battle buttons.
     * @param exitButton If true, only the exit button is enabled.
     */
    void enableBattleButtons(bool exitButton = false);

    /**
     * @brief Disables the battle buttons.
     * @param exitButton If true, only the exit button is disabled.
     */
    void disableBattleButtons(bool exitButton = false);

private:
    QPushButton *attackButton;                      /**< Button used for initiating attacks. */
    QPushButton *pokemonButton;                     /**< Button used for switching pokemons. */
    QPushButton *runButton;                         /**< Button used for leaving the fight. */
    Pokemon *pokemon1;                              /**< First Pokémon displayed on the HUD. */
    Pokemon *pokemon2;                              /**< Second Pokémon displayed on the HUD. */
    QGraphicsPixmapItem *pokemon1Item;              /**< Graphics item for the first Pokémon's image. */
    QGraphicsPixmapItem *pokemon2Item;              /**< Graphics item for the second Pokémon's image. */
    QGraphicsTextItem *health1;                     /**< Text item for the first Pokémon's health. */
    QGraphicsTextItem *health2;                     /**< Text item for the second Pokémon's health. */
    QGraphicsTextItem *menuText;                    /**< Text item for the battle menu. */
    QGraphicsTextItem *attackText;                  /**< Text item for the attack dialogue. */
    QGraphicsPixmapItem *dialogueBox;               /**< Graphics item for battle dialogue. */
    QButtonGroup *moveButtonsGroup;                 /**< Button group for move buttons. */
    QPushButton *backButton;                        /**< Button used for going back. */
    QGraphicsPixmapItem* oldMenPixmap;              /**< Graphics item for the old men. */
    QGraphicsPixmapItem* bossPixmap;                /**< Graphics item for the boss. */
    QProgressBar *pokemon1HealthBar;                /**< Health bar for the first Pokémon. */
    QProgressBar *pokemon2HealthBar;                /**< Health bar for the second Pokémon. */
    QGraphicsProxyWidget *pokemon1HealthBarProxy;   /**< Proxy widget for the first Pokémon's health bar. */
    QGraphicsProxyWidget *pokemon2HealthBarProxy;   /**< Proxy widget for the second Pokémon's health bar. */

    // Helper methods
    /**
    * @brief Creates a QGraphicsPixmapItem from an image file.
    *
    * This function creates a QGraphicsPixmapItem, sets its pixmap to the image at the specified path,
    * resizes it to the specified size, and positions it at the specified coordinates.
    *
    * @param path The file path to the image.
    * @param size The desired size of the pixmap item.
    * @param pos The position to place the pixmap item.
    * @return QGraphicsPixmapItem* A pointer to the created QGraphicsPixmapItem.
    */
    QGraphicsPixmapItem* createPixmapItem(const QString &path, const QSize &size, const QPoint &pos);

    /**
    * @brief Creates a QGraphicsPixmapItem without setting its pixmap.
    *
    * This function creates a QGraphicsPixmapItem and positions it at the specified coordinates.
    * The pixmap should be set later.
    *
    * @param pos The position to place the pixmap item.
    * @return QGraphicsPixmapItem* A pointer to the created QGraphicsPixmapItem.
    */
    QGraphicsPixmapItem* createPixmapItem(const QPoint &pos);

    /**
    * @brief Creates a QGraphicsTextItem with specified color, font, and position.
    *
    * This function creates a QGraphicsTextItem, sets its color and font, and positions it at the specified coordinates.
    *
    * @param color The color of the text.
    * @param font The font of the text.
    * @param pos The position to place the text item.
    * @return QGraphicsTextItem* A pointer to the created QGraphicsTextItem.
    */
    QGraphicsTextItem* createTextItem(const QColor &color, const QFont &font, const QPoint &pos);

    /**
    * @brief Creates a QPushButton with an image and specific dimensions.
    *
    * This function creates a QPushButton, sets its icon to the image at the specified path,
    * resizes it to the specified width and height, and positions it at the specified coordinates.
    *
    * @param path The file path to the button icon image.
    * @param width The width of the button.
    * @param height The height of the button.
    * @param pos The position to place the button.
    * @return QPushButton* A pointer to the created QPushButton.
    */
    QPushButton* createButton(const QString &path, int width, int height, const QPoint &pos);

    /**
    * @brief Creates a move button for a Pokémon move.
    *
    * This function creates a QPushButton for the given move, sets its dimensions, and positions it at the specified coordinates.
    * It also assigns an ID to the button.
    *
    * @param move The move to create a button for.
    * @param pos The position to place the button.
    * @param width The width of the button.
    * @param height The height of the button.
    * @param id The ID to assign to the button.
    */
    void createMoveButton(Move* move, const QPoint &pos, int width, int height, int id);

    /**
    * @brief Updates the graphical representation of a Pokémon.
    *
    * This function updates the pixmap of the provided QGraphicsPixmapItem to represent the given Pokémon.
    * It also adjusts the pixmap orientation based on whether the Pokémon is viewed from the back.
    *
    * @param item The QGraphicsPixmapItem to update.
    * @param pk The Pokémon whose image to display.
    * @param isBack A boolean indicating if the Pokémon is viewed from the back.
    */
    void updatePokemonGraphics(QGraphicsPixmapItem* item, Pokemon* pk, bool isBack);

    /**
    * @brief Applies a shake animation to a QGraphicsPixmapItem.
    *
    * This function applies a shake animation to the given QGraphicsPixmapItem, shaking it for the specified total duration with the specified delay between shakes.
    *
    * @param item The QGraphicsPixmapItem to shake.
    * @param totalDuration The total duration of the shake animation.
    * @param delay The delay between shakes.
    */
    void applyShakeAnimation(QGraphicsPixmapItem* item, int totalDuration, int delay);

    /**
    * @brief Applies a dash animation to a QGraphicsPixmapItem.
    *
    * This function applies a dash animation to the given QGraphicsPixmapItem, moving it incrementally for the specified duration.
    *
    * @param item The QGraphicsPixmapItem to animate.
    * @param duration The duration of the dash animation.
    * @param increment The QPointF value representing the incremental movement.
    */
    void applyDashAnimation(QGraphicsPixmapItem* item, int duration, const QPointF &increment);

    /**
    * @brief Clears all move buttons.
    *
    * This function removes all move buttons from the move buttons group.
    */
    void clearMoveButtons();
};

#endif // BATTLEHUD_H
