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

    Pokemon *getPokemon1() const;
    Pokemon *getPokemon2() const;

private:
    QPushButton *attackButton;
    Pokemon *pokemon1;
    Pokemon *pokemon2;
    QGraphicsPixmapItem *pokemon1Item;
    QGraphicsPixmapItem *pokemon2Item;
    QGraphicsTextItem *health1;
    QGraphicsTextItem *health2;
};

#endif // BATTLEHUD_H
