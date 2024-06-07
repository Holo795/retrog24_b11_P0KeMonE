#include "battle.h"

/**
 * Constructor for the Battle class.
 * Initializes a new battle instance with given player, opponent, and HUD.
 */
Battle::Battle(Player *player1, Pokemon *opponent1, BattleHUD *battleHUD1)
    : itsPlayer1(player1), itsOpponent1(opponent1), itsBattleHUD1(battleHUD1),
    gen(std::random_device{}()) // Seed the generator with random_device
{}

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
void Battle::attack(Move *move, Pokemon *target) {
    std::uniform_int_distribution<> dis(1, 100);  // Distribution for attack calculations
    int random = dis(gen);
    int successRate = move->getItsAccuracy();
    bool crit = random > 94; // 6% chance of critical hit

    Pokemon* attacker = target == itsOpponent1 ? itsPlayer1->getTeam().front() : itsOpponent1;
    Pokemon* defender = target == itsOpponent1 ? itsOpponent1 : itsPlayer1->getTeam().front();

    int lvl = attacker->getLvl();
    int atk = (move->getItsType() == 0) ? attacker->getAtk() : attacker->getSpAtk();
    int def = (move->getItsType() == 0) ? defender->getDef() : defender->getSpDef();

    int damage = move->calculateDamage(lvl, atk, def, crit);

    if (random <= successRate) {
        itsBattleHUD1->frontDashPokemon(attacker);
        itsBattleHUD1->shakePokemon(defender);
        defender->takeDamage(damage);
    }

    itsBattleHUD1->setPokemon(itsPlayer1->getTeam().front(), itsOpponent1);
}


/**
 * @brief Retrieves the boss's team of Pokémon.
 * @return A constant reference to a vector of pointers to Pokémon.
 */
std::vector<Pokemon*> Battle::getBossTeam() const {
    return itsBossTeam;
}
