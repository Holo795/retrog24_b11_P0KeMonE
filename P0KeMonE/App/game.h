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

private:
    Model *model; ///< Pointer to the game model.
    GUI *gui; ///< Pointer to the graphical user interface.
    Player *player = nullptr; ///< Pointer to the player object.
    Battle *battle; ///< Pointer to the current battle context.
    Pokemon *selectedNewPokemon; ///< Pointer to the selected new Pokémon.
    size_t currentDialogueIndex; ///< Index of the current dialogue.
    QGraphicsTextItem *textItem; ///< Pointer to the text item for dialogues.
    QGraphicsPixmapItem *boxItem; ///< Pointer to the box item for dialogues.
    QGraphicsPixmapItem *oldMenItem; ///< Pointer to the box item for dialogues.
    QGraphicsPixmapItem *ballsItem; ///< Pointer to the box item for dialogues.
    std::vector<Pokemon*> itsBossTeam; /**< Vector of Pokémon pointers representing the boss's team. */
    std::vector<Pokemon*> getBossTeam() const;


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;

public slots:

    void setScene(QGraphicsScene *scene); ///< Sets the current scene for the game view.
    void changePokemon(Pokemon *pokemon); ///< Changes the player's active Pokémon.
    void updateView(); ///< Updates the view to ensure the player remains centered.
    void showFight(); ///< Transitions the game to the battle scene.
    void showBossFight(); ///< Transitions the game to the boss battle scene.
    void showOldMenSpeach(); ///< Displays the speach of the old men.
    void continuefight(); ///< Continues the ongoing fight.
    void endFight(bool playerWon); ///< End the ongoing fight.
    void run(); ///< When the run button is clicked
    void generateNewOpponent(); ///< To prepare the next fight
    void showMoves(); ///< Show the moves for the current Pokémon
    void switchPokemon(); ///< Switch the current Pokémon
    void onMoveButtonClicked(QAbstractButton *moveButton);
    void showFightMenu();


public:
    void offerPokemonSwitch();
    void onNewPokemonSelected(Pokemon* newPokemon);
    void onOldPokemonSelected(Pokemon* oldPokemon);
    void showFirstScenario();
    void showNextDialogue();
};

#endif // GAME_H
