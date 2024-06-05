#ifndef GUI_H
#define GUI_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include "model.h"
#include "gameoverhud.h"
#include "maphud.h"
#include "mainhud.h"
#include "battlehud.h"
#include "pokemon.h"


class GUI {

public:

    GUI(Model *model);

    void keyPressEvent(QKeyEvent *event);

    MainHUD * mainMenu();
    GameOverHUD * gameOver();
    MapHUD * map();
    BattleHUD *battle(Pokemon *pk1, Pokemon *pk2);

private:
    Model *model;
    GameOverHUD *gameOverHUD;
    MapHUD *mapHUD;
    MainHUD *mainHUD;
    BattleHUD *battleHUD;

};

#endif // GUI_H
