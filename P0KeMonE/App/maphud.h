#ifndef MAPHUD_H
#define MAPHUD_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include "player.h"
#include "model.h"

class MapHUD : public QGraphicsScene
{
    Q_OBJECT
public:
    MapHUD(Model *model, QObject *parent = nullptr);
    void drawMap();
    void keyPressEvent(QKeyEvent *event);
    Player *getPlayer();

private:
    Model *model; ///< Pointer to the model.
    Player *player; ///< Pointer to the player.
};

#endif // MAPHUD_H
