#include "gui.h"

GUI::GUI(Model *model) {
    this->model = model;
    this->gameOverHUD = new GameOverHUD();
    this->mapHUD = new MapHUD(model);
    this->mainHUD = new MainHUD();
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
    this->battleHUD = new BattleHUD(pk1, pk2);
    return this->battleHUD;
}


void GUI::keyPressEvent(QKeyEvent *event) {
    mapHUD->keyPressEvent(event);
}

