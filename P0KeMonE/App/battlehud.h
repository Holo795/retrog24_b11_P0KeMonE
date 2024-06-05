#ifndef BATTLEHUD_H
#define BATTLEHUD_H

#include <QGraphicsScene>
#include "pokemon.h"

class BattleHUD : public QGraphicsScene {
    Q_OBJECT

public:
    BattleHUD(Pokemon *pk1, Pokemon *pk2, QObject *parent = nullptr);
};

#endif // BATTLEHUD_H
