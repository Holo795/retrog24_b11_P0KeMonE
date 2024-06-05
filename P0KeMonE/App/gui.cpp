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


void GUI::keyPressEvent(QKeyEvent *event) {
    mapHUD->keyPressEvent(event);
}
