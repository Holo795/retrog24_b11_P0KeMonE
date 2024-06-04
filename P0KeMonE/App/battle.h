#ifndef BATTLE_H
#define BATTLE_H

#include "battlehud.h"
#include "player.h"
#include "pokemon.h"
class Battle
{
private:
    Player *itsPlayer1;
    Pokemon *itsPokemon1;
    BattleHUD *itsBattleHUM1;
public:
    Battle(Player *player1, Pokemon *pokemon1, BattleHUD *battleHUM1);
    void attack(Move *move, Pokemon *target);

};

#endif // BATTLE_H
