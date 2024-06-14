#include "move.h"


Move::Move(std::string itsName, int itsPower, int itsAccuracy, MOVENATURE itsNature, PKTYPE itsType)
{
    this->itsName = itsName;
    this->itsPower = itsPower;
    this->itsAccuracy = itsAccuracy;
    this->itsNature = itsNature;
    this->itsType = itsType;
}

std::string Move::getItsName() const
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

MOVENATURE Move::getItsNature() const
{
    return itsNature;
}

std::string Move::getItsTextNature(int nature) const
{
    switch (nature) {
    case Physique: return "Physic";
    case Spéciale: return "Special";
    default: return "Inconnu";
    }
}


PKTYPE Move::getItsType() const
{
    return itsType;
}

std::string Move::getItsTextType(int type) const
{
    switch (type) {
    case Grass: return "Grass";
    case Poison: return "Poison";
    case Normal: return "Normal";
    case Bug: return "Bug";
    case Psychic: return "Psychic";
    case Ghost: return "Ghost";
    case Ground: return "Ground";
    case Dragon: return "Dragon";
    case Fairy: return "Fairy";
    case Fire: return "Fire";
    case Fighting: return "Fighting";
    case Dark: return "Dark";
    case Electric: return "Electric";
    case Flying: return "Flying";
    case Rock: return "Rock";
    case Steel: return "Steel";
    case Water: return "Water";
    case Ice: return "Ice";
    default: return "Inconnu";
    }
}

int Move::calculateDamage(int lvl, int atk, int def, bool crit) const
{
    int level = lvl;
    int attackStat = atk;
    int defenseStat = def;
    int power = itsPower;

    double critical = crit ? 2.0 : 1.0;

    double baseDamage = (((((level * 0.4 + 2) * attackStat * power) / (defenseStat * 50)) + 2) * critical);

    // Ensure damage is at least 1
    return std::max(1, static_cast<int>(baseDamage));
}
