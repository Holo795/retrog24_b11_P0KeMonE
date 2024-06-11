/**
 * @file Game.h
 * @brief Defines the Game class, which is responsible for the main game view and interactions in a Pokémon-like game.
 */

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QKeyEvent>

#include "battle.h"
#include "model.h"
#include "gui.h"

/**
 * @class Game
 * @brief Manages the main game interactions and UI updates.
 *
 * This class is a custom QGraphicsView that handles all user interactions and display updates for the game,
 * including moving between different screens such as the main menu, game map, and battle scenes.
 */
class Game : public QGraphicsView
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a Game object with model and GUI dependencies.
     * @param model Pointer to the model, which handles the game logic.
     * @param gui Pointer to the GUI, which manages all graphical components.
     * @param parent Pointer to the parent widget, default is nullptr.
     */
    Game(Model *model, GUI *gui, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

    /**
     * @brief Sets the boss's team of Pokémon.
     * @param team Vector of pointers to Pokémon representing the boss's team.
     */
    void setBossTeam(std::vector<Pokemon*> team);

    /**
     * @brief Retrieves the boss's team of Pokémon.
     * @return A constant reference to a vector of pointers to Pokémon.
     */
    std::vector<Pokemon*> getBossTeam() const;

protected:
    /**
     * @brief Handle key press events for game interactions.
     * @param event Pointer to the QKeyEvent.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Handle mouse press events to prevent loss of focus.
     * @param event Pointer to the QMouseEvent.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Handle mouse double-click events.
     */
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    /**
     * @brief Handle focus out events.
     */
    void focusOutEvent(QFocusEvent *event) override;

    /**
     * @brief Handle focus in events.
     */
    void focusInEvent(QFocusEvent *event) override;

public slots:
    /**
     * @brief Sets the current scene for the game view.
     * @param scene Pointer to the QGraphicsScene.
     */
    void setScene(QGraphicsScene *scene);

    /**
     * @brief Changes the player's active Pokémon.
     * @param pokemon Pointer to the new Pokémon.
     */
    void changePokemon(Pokemon *pokemon);

    /**
     * @brief Updates the view to ensure the player remains centered.
     */
    void updateView();

    /**
     * @brief Transitions the game to the battle scene.
     */
    void showFight();

    /**
     * @brief Transitions the game to the boss battle scene.
     */
    void showBossFight();

    /**
     * @brief Displays the speech of the old man.
     */
    void showOldMenSpeach();

    /**
     * @brief Continues the ongoing fight.
     */
    void continueFight();

    /**
     * @brief Ends the ongoing fight.
     * @param playerWon Boolean indicating if the player won the fight.
     */
    void endFight(bool playerWon);

    /**
     * @brief Handles running from a battle.
     */
    void run();

    /**
     * @brief Generates a new opponent Pokémon.
     */
    void generateNewOpponent();

    /**
     * @brief Displays the player's Pokémon moves.
     */
    void showMoves();

    /**
     * @brief Switches to the Pokémon selection scene.
     */
    void switchPokemon();

    /**
     * @brief Handles move button clicks during battle.
     * @param moveButton Pointer to the clicked button.
     */
    void onMoveButtonClicked(QAbstractButton *moveButton);

    /**
     * @brief Displays the fight menu.
     */
    void showFightMenu();

public:
    /**
     * @brief Offers the player a Pokémon switch.
     */
    void offerPokemonSwitch();

    /**
     * @brief Handles the event when a new Pokémon is selected.
     * @param newPokemon Pointer to the new Pokémon.
     */
    void onNewPokemonSelected(Pokemon* newPokemon);

    /**
     * @brief Handles the event when an old Pokémon is selected for removal.
     * @param oldPokemon Pointer to the old Pokémon.
     */
    void onOldPokemonSelected(Pokemon* oldPokemon);

    /**
     * @brief Displays the first scenario.
     */
    void showFirstScenario();

    /**
     * @brief Displays the next dialogue in the sequence.
     */
    void showNextDialogue();

private:
    Model *model; ///< Pointer to the game model.
    GUI *gui; ///< Pointer to the graphical user interface.
    Player *player; ///< Pointer to the player object.
    Battle *battle; ///< Pointer to the current battle context.
    Pokemon *selectedNewPokemon; ///< Pointer to the selected new Pokémon.
    size_t currentDialogueIndex; ///< Index of the current dialogue.
    QGraphicsTextItem *textItem; ///< Pointer to the text item for dialogues.
    QGraphicsPixmapItem *boxItem; ///< Pointer to the box item for dialogues.
    QGraphicsPixmapItem *oldMenItem; ///< Pointer to the old man item for dialogues.
    QGraphicsPixmapItem *ballsItem; ///< Pointer to the balls item for dialogues.
    std::vector<Pokemon*> itsBossTeam; ///< Vector of Pokémon pointers representing the boss's team.
    SoundManager *soundManager; ///< Pointer to the sound manager.

    /**
     * @brief Setup connections for player encounters and button clicks.
     */
    void setupConnections();

    /**
     * @brief Reset the game to its initial state.
     */
    void resetGame();

    /**
     * @brief Create a QGraphicsPixmapItem.
     * @param pixmapPath Path to the pixmap resource.
     * @param pos Position of the item.
     * @param size Optional size to scale the pixmap.
     * @return Pointer to the created QGraphicsPixmapItem.
     */
    QGraphicsPixmapItem* createGraphicsItem(const QString &pixmapPath, const QPointF &pos, const QSize &size);

    /**
     * @brief Setup the text item for displaying dialogues.
     */
    void setupTextItem();

    /**
     * @brief Disable battle buttons.
     */
    void disableBattleButtons();

    /**
     * @brief Enable battle buttons.
     */
    void enableBattleButtons();

    /**
     * @brief Handle the event when a Pokémon faints.
     * @param faintedPokemon Pointer to the fainted Pokémon.
     */
    void handlePokemonFainted(Pokemon* faintedPokemon);

    /**
     * @brief Handle swapping Pokémon when the player's team is full.
     * @param newPokemons Vector of pointers to the new Pokémon.
     */
    void handlePokemonSwap(const std::vector<Pokemon*>& newPokemons);
};

#endif // GAME_H
