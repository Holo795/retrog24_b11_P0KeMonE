#ifndef BATTLE_H
#define BATTLE_H

#include "battlehud.h"
#include "player.h"
#include "pokemon.h"
class Battle
{
private:
    Player *itsPlayer1;
    Pokemon *itsOpponent1;
    BattleHUD *itsBattleHUD1;
public:
    Battle(Player *itsPlayer1, Pokemon *opponent1, BattleHUD *battleHUD1);
    void attack(Move *move, Pokemon *target);

};

#endif // BATTLE_H
