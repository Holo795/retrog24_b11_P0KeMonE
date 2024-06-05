#include "battle.h"
#include <cstdlib>
#include <ctime>

Battle::Battle(Player *player1, Pokemon *opponent1, BattleHUD *battleHUD1)
{

    itsPlayer1 = player1;
    this->itsOpponent1 = opponent1;
    this->itsBattleHUD1 = battleHUD1;
}

void Battle::attack(Move *move, Pokemon *target)
{
    // Initialiser le générateur de nombres aléatoires
    srand(time(0));
    int max = 100;
    int random = rand() % max + 1;
    int successRate = move->getItsAccuracy();
    int atk, def, lvl, damage;
    bool crit = random>6;

    Pokemon* pokemon1 = itsPlayer1->getTeam().front();
    if (target == itsOpponent1)
    {
        lvl = pokemon1->getLvl();
        if(move->getItsType() == 0) //physique
        {
            atk = pokemon1->getAtk();
            def = itsOpponent1->getDef();
            damage = move->calculateDamage(lvl,atk,def,crit);
        }
        else if (move->getItsType() == 1) //special
        {
            atk = pokemon1->getSpAtk();
            def = itsOpponent1->getSpDef();
            damage = move->calculateDamage(lvl,atk,def,crit);
        }

    }
    else
    {
        lvl = itsOpponent1->getLvl();
        if(move->getItsType() == 0) //physique
        {
            atk = itsOpponent1->getAtk();
            def = pokemon1->getDef();
            damage = move->calculateDamage(lvl,atk,def,crit);
        }
        else if (move->getItsType() == 1) //special
        {
            atk = itsOpponent1->getSpAtk();
            def = pokemon1->getSpDef();
            damage = move->calculateDamage(lvl,atk,def,crit);
        }
    }
    if (random <= successRate)
    {
        target->takeDamage(damage);
    }

    itsBattleHUD1->setPokemon(itsPlayer1->getTeam().front(), itsOpponent1);




}
