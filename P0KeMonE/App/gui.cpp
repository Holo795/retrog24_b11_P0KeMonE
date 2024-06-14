#include "gui.h"

GUI::GUI(Model *model) : model(model) {
    this->gameOverHUD = new GameOverHUD();
    this->mapHUD = new MapHUD(model);
    this->mainHUD = new MainHUD();
    this->battleHUD = new BattleHUD();
    this->playerHUD = new PlayerHUD();
}

GUI::~GUI() {
    delete gameOverHUD;
    delete mapHUD;
    delete mainHUD;
    delete battleHUD;
    delete playerHUD;
}

MainHUD * GUI::mainMenu() {
    return mainHUD;
}

GameOverHUD * GUI::gameOver() {
    return gameOverHUD;
}

MapHUD * GUI::map() {
    return mapHUD;
}

BattleHUD *GUI::battle(Pokemon *pk1, Pokemon *pk2) {
    battleHUD->setPokemon(pk1, pk2);
    return battleHUD;
}

BattleHUD *GUI::battle() {
    return battleHUD;
}

PlayerHUD *GUI::playerTeam(vector<Pokemon *> pokemons, int itsLevel) {
    playerHUD->setPokemons(pokemons, itsLevel);
    playerHUD->setSelectionMode(false);
    playerHUD->setPokemonLabel("Your team");
    return playerHUD;
}

PlayerHUD *GUI::team() {
    return playerHUD;
}

PlayerHUD *GUI::selectPokemon(vector<Pokemon *> pokemons, string text) {
    playerHUD->setSelectionMode(true);
    playerHUD->setPokemonLabel(text);
    playerHUD->setPokemons(pokemons,0);

    return playerHUD;
}
