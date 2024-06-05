#include "move.h"

string Move::getItsName() const
{
    return itsName;
}

int Move::getItsPower() const
{
    return itsPower;
}

int Move::getItsAccuracy() const
{
    return itsAccuracy;
}

MOVENATURE Move::getItsType() const
{
    return itsType;
}

Move::Move(string itsName, int itsPower, int itsAccuracy, MOVENATURE itsType)
{
    this->itsName = itsName;
    this->itsPower = itsPower;
    this->itsAccuracy = itsAccuracy;
    this->itsType = itsType;
}

int Move::calculateDamage(int lvl, int atk, int def, bool crit) const
{
    int level = lvl;
    int attackStat = atk;  // Ou getSpAtk() si c'est une attaque spéciale
    int defenseStat = def; // Ou getSpDef() si c'est une attaque spéciale
    int power = itsPower;

    double critical = crit ? 2.0 : 1.0;

    double baseDamage = (((((level * 0.4 + 2) * attackStat * power) / (defenseStat * 50)) + 2) * critical);

    return std::max(1, static_cast<int>(baseDamage));
}


Move::~Move()
{

}

