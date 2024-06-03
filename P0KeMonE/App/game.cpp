#include "game.h"

Game::Game(Model *model, GUI *gui) {
    model->loadMap(":/maps/map.txt");
    gui->drawMap();
}
