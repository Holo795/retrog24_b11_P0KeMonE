#include "gui.h"

/**
 * @brief Constructor for GUI, initializes all HUDs using a given model.
 * @param model Pointer to the model used for game data and logic.
 */
GUI::GUI(Model *model) : model(model) {
    // Initialize HUDs for various game scenes
    gameOverHUD = new GameOverHUD();
    mapHUD = new MapHUD(model);
    mainHUD = new MainHUD();
    battleHUD = new BattleHUD();
    playerHUD = new PlayerHUD();
}

/**
 * @brief Destructor for the GUI class.
 */
GUI::~GUI() {
    // Delete all HUDs
    delete gameOverHUD;
    delete mapHUD;
    delete mainHUD;
    delete battleHUD;
    delete playerHUD;
}

/**
 * @brief Accessor for the main menu HUD.
 * @return Pointer to the MainHUD object.
 */
MainHUD* GUI::mainMenu() const {
    return mainHUD;
}

/**
 * @brief Accessor for the game over HUD.
 * @return Pointer to the GameOverHUD object.
 */
GameOverHUD* GUI::gameOver() const {
    return gameOverHUD;
}

/**
 * @brief Accessor for the map HUD.
 * @return Pointer to the MapHUD object.
 */
MapHUD* GUI::map() const {
    return mapHUD;
}

/**
 * @brief Returns the battle HUD initialized with specific Pokémon.
 * @param pk1 Pointer to the first Pokémon.
 * @param pk2 Pointer to the second Pokémon.
 * @return Pointer to the BattleHUD object.
 */
BattleHUD* GUI::battle(Pokemon *pk1, Pokemon *pk2) const {
    // Set the Pokémon in the battle HUD before returning it
    battleHUD->setPokemon(pk1, pk2);
    return battleHUD;
}

/**
 * @brief Accessor for the default battle HUD.
 * @return Pointer to the BattleHUD object.
 */
BattleHUD* GUI::battle() const {
    return battleHUD;
}

/**
 * @brief Accessor for the player HUD.
 * @param pokemons A vector of pointers to the player's Pokémon.
 * @param itsLevel The level of the player.
 * @return Pointer to the PlayerHUD object.
 */
PlayerHUD* GUI::playerTeam(const std::vector<Pokemon*>& pokemons, int itsLevel) const {
    // Set the Pokémon in the player HUD before returning it
    playerHUD->setPokemons(pokemons, itsLevel);
    playerHUD->setSelectionMode(false);
    return playerHUD;
}

/**
 * @brief Accessor for the player HUD.
 * @return Pointer to the PlayerHUD object.
 */
PlayerHUD* GUI::team() const {
    return playerHUD;
}

/**
 * @brief Accessor for the player HUD.
 * @param pokemons A vector of pointers to the player's Pokémon.
 * @return Pointer to the PlayerHUD object.
 */
PlayerHUD* GUI::selectPokemon(const std::vector<Pokemon*>& pokemons) const {
    // Set the Pokémon in the player HUD before returning it
    playerHUD->setSelectionMode(true);
    playerHUD->setPokemons(pokemons, 1);
    return playerHUD;
}
