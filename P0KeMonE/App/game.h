/**
 * @file Game.h
 * @brief Defines the Game class, which is responsible for the main game view and interactions in a Pokémon-like game.
 */

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QFontDatabase>
#include <QGraphicsView>
#include <QProcess>
#include <QKeyEvent>

#include "savemanager.h"
#include "battle.h"
#include "model.h"
#include "gui.h"

/**
 * @class Game
 * @brief Manages the main game interactions and UI updates.
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

private:
    Model *model;                       ///< Pointer to the game model.
    GUI *gui;                           ///< Pointer to the graphical user interface.
    Player *player = nullptr;           ///< Pointer to the player object.
    Battle *battle;                     ///< Pointer to the current battle context.
    size_t currentDialogueIndex = 0;    ///< Index of the current dialogue.
    std::vector<Pokemon*> itsBossTeam;  ///< Vector of Pokémon pointers representing the boss's team. */
    bool itsBossFight = false;          ///< Flag indicating if a boss fight is occurring.
    bool itsFirstFight = false;         ///< Flag indicating if this is the first fight.
    bool itsInFight = false;            ///< Flag indicating if a fight is currently occurring.
    bool statepokemonChanged = false;   ///< Flag to indicate if the Pokémon has changed.$
    SoundManager *soundManager;          ///< The sound manager for the game.
    SaveManager *saveManager;

    /**
     * @brief Ends the ongoing fight.
     * @param playerWon Boolean indicating if the player won the fight.
     */
    void endFight(bool playerWon);

    /**
     * @brief Sets the current scene for the game view.
     * @param scene Pointer to the QGraphicsScene to set.
     */
    void setScene(QGraphicsScene *scene);

    /**
     * @brief Restarts the game.
     */
    void restartGame();

    /**
     * @brief Handles the space key press event based on the current scene.
     * @param currentScene The current scene identifier.
     */
    void handleSpaceKeyPress(QString currentScene);

    /**
     * @brief Handles the escape and 'I' key press events based on the current scene.
     * @param currentScene The current scene identifier.
     */
    void handleEscIKeyPress(QString currentScene);

    /**
     * @brief Handles the space key press event in the main menu.
     */
    void handleMainMenuSpaceKeyPress();

protected:
    /**
     * @brief Handles key press events.
     * @param event Pointer to the QKeyEvent.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Handles mouse press events.
     * @param event Pointer to the QMouseEvent.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Handles mouse double-click events.
     * @param event Pointer to the QMouseEvent.
     */
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    /**
     * @brief Handles focus out events.
     * @param event Pointer to the QFocusEvent.
     */
    void focusOutEvent(QFocusEvent *event) override;

    /**
     * @brief Handles focus in events.
     * @param event Pointer to the QFocusEvent.
     */
    void focusInEvent(QFocusEvent *event) override;

public slots:
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
     * @brief Continues the ongoing fight.
     */
    void continuefight();

    /**
     * @brief Handles the run button click event.
     */
    void run();

    /**
     * @brief Displays the moves for the current Pokémon.
     */
    void showMoves();

    /**
     * @brief Switches the current Pokémon.
     */
    void switchPokemon();

    /**
     * @brief Handles move button click events.
     * @param moveButton Pointer to the clicked move button.
     */
    void onMoveButtonClicked(QAbstractButton *moveButton);

    /**
     * @brief Shows the fight menu.
     */
    void showFightMenu();

    /**
     * @brief Shows the first fight scene.
     */
    void showFirstFight();

public:
    /**
     * @brief Displays the next dialogue in the sequence.
     */
    void showNextDialogue();
};

#endif // GAME_H
