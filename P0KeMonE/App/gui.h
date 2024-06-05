#ifndef GUI_H
#define GUI_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include "model.h"
#include "gameoverhud.h"
#include "maphud.h"
#include "mainhud.h"


class GUI {

public:

    GUI(Model *model);

    void keyPressEvent(QKeyEvent *event);

    MainHUD * mainMenu();
    GameOverHUD * gameOver();
    MapHUD * map();

private:
    Model *model;
    GameOverHUD *gameOverHUD;
    MapHUD *mapHUD;
    MainHUD *mainHUD;
};

#endif // GUI_H
