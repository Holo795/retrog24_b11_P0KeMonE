#ifndef GAME_H
#define GAME_H

#include "model.h"
#include "gui.h"

class Game
{
public:
    /**
     * @brief Game constructor defining the Model and GUI
     * Loads the map and draws it on the GUI
     * @param model Pointer to the model
     * @param gui Pointer to the GUI
     */
    Game(Model *model, GUI *gui);
};

#endif // GAME_H
