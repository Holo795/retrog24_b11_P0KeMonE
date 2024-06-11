#include "battle.h"

/**
 * Constructor for the Battle class.
 * Initializes a new battle instance with given player, opponent, and HUD.
 */
Battle::Battle(Pokemon *opponent1, Pokemon *opponent2, BattleHUD *battleHUD)
    : itsOpponent1(opponent1), itsOpponent2(opponent2), itsBattleHUD(battleHUD),
    gen(std::random_device{}()) // Seed the generator with random_device
{

}

/**
 * Destructor for the Battle class.
 */
Battle::~Battle()
{
    delete itsOpponent1;
    delete itsOpponent2;
    delete itsBattleHUD;
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

    Pokemon* attacker = target == itsOpponent2 ? itsOpponent1 : itsOpponent2;
    Pokemon* defender = target == itsOpponent2 ? itsOpponent2 : itsOpponent1;

    int lvl = attacker->getLvl();
    int atk = (move->getItsNature() == 0) ? attacker->getAtk() : attacker->getSpAtk();
    int def = (move->getItsNature() == 0) ? defender->getDef() : defender->getSpDef();

    int damage = move->calculateDamage(lvl, atk, def, crit);


    if (random <= successRate) {
        itsBattleHUD->frontDashPokemon(attacker);
        itsBattleHUD->shakePokemon(defender);
        defender->takeDamage(damage);
        itsBattleHUD->setText(QString::fromStdString(attacker->getItsName() + " used " + move->getItsName() + "!"));

    } else {
        itsBattleHUD->setText(QString::fromStdString(attacker->getItsName() + " used " + move->getItsName() + " and missed !"));

    }
    itsBattleHUD->setPokemon(itsOpponent1, itsOpponent2);
}


/**
 * @brief Retrieves the battle HUD.
 * @return Pointer to the battle HUD.
 */
BattleHUD *Battle::getBattleHUD()
{
    return itsBattleHUD;
}
