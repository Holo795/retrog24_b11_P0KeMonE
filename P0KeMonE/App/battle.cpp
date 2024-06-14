#include "battle.h"

Battle::Battle(Pokemon *opponent1, Pokemon *opponent2, BattleHUD *battleHUD)
    : gen(std::random_device{}()), itsOpponent1(opponent1), itsOpponent2(opponent2),
    itsBattleHUD(battleHUD)
{}

Battle::~Battle()
{
    delete itsOpponent1;
    delete itsOpponent2;
    delete itsBattleHUD;
}

void Battle::attack(Move *move, Pokemon *target) {
    std::uniform_int_distribution<> dis(1, 100);
    int random = dis(gen);
    int successRate = move->getItsAccuracy();
    bool crit = random > 94;

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
        itsBattleHUD->setText(attacker->getItsName() + " used " + move->getItsName() + "!");

    } else {
        itsBattleHUD->setText(attacker->getItsName() + " used " + move->getItsName() + " and missed !");

    }
    itsBattleHUD->updateHealthBars();
    itsBattleHUD->setPokemon(itsOpponent1, itsOpponent2);
}
