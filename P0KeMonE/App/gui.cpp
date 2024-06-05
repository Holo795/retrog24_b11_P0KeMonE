#include "gui.h"

GUI::GUI(Model *model) {
    this->model = model;
    this->gameOverHUD = new GameOverHUD();
    this->mapHUD = new MapHUD(model);
    this->mainHUD = new MainHUD();
    this->battleHUD = new BattleHUD();
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

BattleHUD *GUI::battle(Pokemon * pk1, Pokemon * pk2)
{
    battleHUD->setPokemon(pk1, pk2);
    return battleHUD;
}

BattleHUD *GUI::battle()
{
    return battleHUD;
}

