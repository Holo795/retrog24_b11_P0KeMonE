#include "battle.h"
#include <cstdlib>
#include <ctime>

Battle::Battle(Player *player1, Pokemon *pokemon1, BattleHUD *battleHUM1)
{
    this->itsPlayer1 = player1;
    this->itsPokemon1 = pokemon1;
    this->itsBattleHUM1 = battleHUM1;
}

void Battle::attack(Move *move, Pokemon *target)
{
    // Initialiser le générateur de nombres aléatoires
    srand(time(0));
    int max = 100;
    int chancesucces = move->getItsAccuracy();

    if(move->getItsType() == 0)
   {
        int random = (rand() % max) + 1;
        if (random <= chancesucces)
        {
            target->takeDamage(move->getItsPower());
        }
    }
    else if (move->getItsType() == 1)
    {
        int random = (rand() % max) + 1;
        if (random <= chancesucces)
        {
            target->takeDamage(move->getItsPower());
        }
    }
}
