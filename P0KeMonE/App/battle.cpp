#include "battle.h"
#include <cstdlib>
#include <ctime>

/**
 * Constructor for the Battle class.
 * Initializes a new battle instance with given player, opponent, and HUD.
 */
Battle::Battle(Player *player1, Pokemon *opponent1, BattleHUD *battleHUD1)
{
    itsPlayer1 = player1;
    itsOpponent1 = opponent1;
    itsBattleHUD1 = battleHUD1;
}

/**
 * Destructor for the Battle class.
 */
Battle::~Battle()
{
    delete itsPlayer1;
    delete itsOpponent1;
    delete itsBattleHUD1;
}

/**
 * Conducts an attack in a battle scenario using a specified move against a target Pokémon.
 * The function determines the damage based on move type and calculates whether the attack hits based on move accuracy.
 */
void Battle::attack(Move *move, Pokemon *target)
{
    // Initialize random number generator for attack calculations
    srand(time(0));
    int max = 100;
    int random = rand() % max + 1;
    int successRate = move->getItsAccuracy();
    int atk, def, lvl, damage;
    bool crit = random > 6; // Determines if a critical hit occurs

    Pokemon* pokemon1 = itsPlayer1->getTeam().front(); // Retrieves the first Pokémon from the player's team
    if (target == itsOpponent1) // Determine level and stats based on whether the target is the opponent
    {
        lvl = pokemon1->getLvl();
        if (move->getItsType() == 0) // Physical attack
        {
            atk = pokemon1->getAtk();
            def = itsOpponent1->getDef();
            damage = move->calculateDamage(lvl, atk, def, crit);
        }
        else if (move->getItsType() == 1) // Special attack
        {
            atk = pokemon1->getSpAtk();
            def = itsOpponent1->getSpDef();
            damage = move->calculateDamage(lvl, atk, def, crit);
        }
    }
    else // Handling when the opponent attacks the player's Pokémon
    {
        lvl = itsOpponent1->getLvl();
        if (move->getItsType() == 0) // Physical attack
        {
            atk = itsOpponent1->getAtk();
            def = pokemon1->getDef();
            damage = move->calculateDamage(lvl, atk, def, crit);
        }
        else if (move->getItsType() == 1) // Special attack
        {
            atk = itsOpponent1->getSpAtk();
            def = pokemon1->getSpDef();
            damage = move->calculateDamage(lvl, atk, def, crit);
        }
    }
    if (random <= successRate) // Apply damage if attack is successful
    {
        itsBattleHUD1->frontDashPokemon(target == itsOpponent1 ? pokemon1 : itsOpponent1);
        itsBattleHUD1->shakePokemon(target);
        target->takeDamage(damage);
    }

    // Update the battle HUD with the current status of player and opponent Pokémon
    itsBattleHUD1->setPokemon(itsPlayer1->getTeam().front(), itsOpponent1);
}
