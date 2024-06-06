#include "gui.h"

/**
 * Initializes the GUI class, setting up HUDs for different parts of the game.
 */
GUI::GUI(Model *model) : model(model) {
    // Initialize HUDs for various game scenes
    this->gameOverHUD = new GameOverHUD();
    this->mapHUD = new MapHUD(model);
    this->mainHUD = new MainHUD();
    this->battleHUD = new BattleHUD();
    this->playerHUD = new PlayerHUD();
}

/**
 * Destructor for the GUI class.
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
 * Returns the main menu HUD.
 */
MainHUD * GUI::mainMenu() {
    return mainHUD;
}

/**
 * Returns the game over HUD.
 */
GameOverHUD * GUI::gameOver() {
    return gameOverHUD;
}

/**
 * Returns the map HUD.
 */
MapHUD * GUI::map() {
    return mapHUD;
}

/**
 * Initializes the battle HUD with two specific Pokémon and returns it.
 */
BattleHUD *GUI::battle(Pokemon *pk1, Pokemon *pk2) {
    // Set the Pokémon in the battle HUD before returning it
    battleHUD->setPokemon(pk1, pk2);
    return battleHUD;
}

/**
 * Returns the default battle HUD, typically used when no specific Pokémon are set.
 */
BattleHUD *GUI::battle() {
    return battleHUD;
}

/**
 * Initializes the player HUD with a specific player object and returns it.
 */
PlayerHUD *GUI::playerTeam(vector<Pokemon *> pokemons, int itsLevel) {
    // Set the player in the player HUD before returning it
    playerHUD->setPokemons(pokemons, itsLevel);
    playerHUD->setSelectionMode(false);
    return playerHUD;
}

/**
 * Returns the player HUD.
 */
PlayerHUD *GUI::TeamHUD() {
    return playerHUD;
}

/**
 * Initializes the player HUD with a specific player object and returns it.
 */
PlayerHUD *GUI::selectPokemon(vector<Pokemon *> pokemons) {
    // Set the player in the player HUD before returning it
    playerHUD->setSelectionMode(true);
    playerHUD->setPokemons(pokemons,0);
    return playerHUD;
}
