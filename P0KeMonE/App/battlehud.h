#ifndef BATTLEHUD_H
#define BATTLEHUD_H

#include <QGraphicsScene>
#include <QPushButton>
#include "pokemon.h"

class BattleHUD : public QGraphicsScene {
    Q_OBJECT

public:
    BattleHUD(QObject *parent = nullptr);
    QPushButton *getAttackButton();
    void setPokemon(Pokemon *pk1, Pokemon *pk2);

private:
    QPushButton *attackButton;
};

#endif // BATTLEHUD_H
