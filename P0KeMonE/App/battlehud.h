/**
 * @file BattleHUD.h
 * @author Paulin Paul Achile Lilian
 * @brief Defines the BattleHUD class, which handles the graphical user interface for battles in a Pokémon game.
 */

#ifndef BATTLEHUD_H
#define BATTLEHUD_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QButtonGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QButtonGroup>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QGraphicsProxyWidget>
#include <QProgressBar>

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
    QPushButton *attackButton;           /**< Button used for initiating attacks. */
    QPushButton *pokemonButton;          /**< Button used for switching pokemons. */
    QPushButton *runButton;              /**< Button used for leaving the fight. */
    Pokemon *pokemon1;                   /**< First Pokémon displayed on the HUD. */
    Pokemon *pokemon2;                   /**< Second Pokémon displayed on the HUD. */
    QGraphicsPixmapItem *pokemon1Item;   /**< Graphics item for the first Pokémon's image. */
    QGraphicsPixmapItem *pokemon2Item;   /**< Graphics item for the second Pokémon's image. */
    QGraphicsTextItem *health1;          /**< Text item for the first Pokémon's health. */
    QGraphicsTextItem *health2;          /**< Text item for the second Pokémon's health. */
    QGraphicsTextItem *menuText;         /**< Text item for the battle menu. */
    QGraphicsTextItem *attackText;       /**< Text item for the attack dialogue. */
    QGraphicsPixmapItem *dialogueBox;    /**< Graphics item for battle dialogue. */
    QButtonGroup *moveButtonsGroup;      /**< Button group for move buttons. */
    QPushButton *backButton;             /**< Button used for going back. */
    QGraphicsPixmapItem* oldMenPixmap;   /**< Graphics item for the old men. */
    QGraphicsPixmapItem* bossPixmap;     /**< Graphics item for the boss. */
    QProgressBar *pokemon1HealthBar;     /**< Health bar for the first Pokémon. */
    QProgressBar *pokemon2HealthBar;     /**< Health bar for the second Pokémon. */
    QGraphicsProxyWidget *pokemon1HealthBarProxy; /**< Proxy widget for the first Pokémon's health bar. */
    QGraphicsProxyWidget *pokemon2HealthBarProxy; /**< Proxy widget for the second Pokémon's health bar. */

    // Helper methods
    QGraphicsPixmapItem* createPixmapItem(const QString &path, const QSize &size, const QPoint &pos);
    QGraphicsPixmapItem* createPixmapItem(const QPoint &pos);
    QPushButton* createButton(const QString &path, int width, int height, const QPoint &pos);
    QGraphicsTextItem* createTextItem(const QColor &color, const QFont &font, const QPoint &pos);
    void updatePokemonGraphics(QGraphicsPixmapItem* item, Pokemon* pk, bool isBack);
    void applyShakeAnimation(QGraphicsPixmapItem* item, int totalDuration, int delay);
    void applyDashAnimation(QGraphicsPixmapItem* item, int duration, const QPointF &increment);
    void clearMoveButtons();
    void createMoveButton(Move* move, const QPoint &pos, int width, int height, int id);
};

#endif // BATTLEHUD_H
