/**
 * @file GUI.h
 * @brief Defines the GUI class that handles graphical user interfaces for different game scenes.
 */

#ifndef GUI_H
#define GUI_H

#include <QGraphicsScene>
#include "model.h"
#include "gameoverhud.h"
#include "maphud.h"
#include "mainhud.h"
#include "battlehud.h"
#include "playerhud.h"
#include "pokemon.h"

/**
 * @class GUI
 * @brief Manages all GUI elements in the game including main menu, game over, map, and battle screens.
 *
 * This class is responsible for creating and managing all the HUDs used in the game. It provides
 * methods to access different screens and handles their initialization.
 */
class GUI {
public:
    /**
     * @brief Constructor for GUI, initializes all HUDs using a given model.
     * @param model Pointer to the model used for game data and logic.
     */
    GUI(Model *model);

    /**
     * @brief Destructor for the GUI class.
     */
    ~GUI();

    /**
     * @brief Accessor for the main menu HUD.
     * @return Pointer to the MainHUD object.
     */
    MainHUD* mainMenu() const;

    /**
     * @brief Accessor for the game over HUD.
     * @return Pointer to the GameOverHUD object.
     */
    GameOverHUD* gameOver() const;

    /**
     * @brief Accessor for the map HUD.
     * @return Pointer to the MapHUD object.
     */
    MapHUD* map() const;

    /**
     * @brief Returns the battle HUD initialized with specific Pokémon.
     * @param pk1 Pointer to the first Pokémon.
     * @param pk2 Pointer to the second Pokémon.
     * @return Pointer to the BattleHUD object.
     */
    BattleHUD* battle(Pokemon *pk1, Pokemon *pk2) const;

    /**
     * @brief Accessor for the default battle HUD.
     * @return Pointer to the BattleHUD object.
     */
    BattleHUD* battle() const;

    /**
     * @brief Accessor for the player HUD.
     * @param pokemons A vector of pointers to the player's Pokémon.
     * @param itsLevel The level of the player.
     * @return Pointer to the PlayerHUD object.
     */
    PlayerHUD* playerTeam(const std::vector<Pokemon*>& pokemons, int itsLevel) const;

    /**
     * @brief Accessor for the player HUD.
     * @return Pointer to the PlayerHUD object.
     */
    PlayerHUD* team() const;

    /**
     * @brief Accessor for the player HUD.
     * @param pokemons A vector of pointers to the player's Pokémon.
     * @return Pointer to the PlayerHUD object.
     */
    PlayerHUD* selectPokemon(const std::vector<Pokemon*>& pokemons) const;

private:
    Model *model; ///< Pointer to the game model.
    GameOverHUD *gameOverHUD; ///< Pointer to the game over HUD.
    MapHUD *mapHUD; ///< Pointer to the map HUD.
    MainHUD *mainHUD; ///< Pointer to the main menu HUD.
    BattleHUD *battleHUD; ///< Pointer to the battle HUD.
    PlayerHUD *playerHUD; ///< Pointer to the player HUD.
};

#endif // GUI_H
