#include "move.h"


Move::Move(string itsName, int itsPower, int itsAccuracy, MOVENATURE itsNature, PKTYPE itsType)
{
    this->itsName = itsName;
    this->itsPower = itsPower;
    this->itsAccuracy = itsAccuracy;
    this->itsNature = itsNature;
    this->itsType = itsType;
}

/**
 * Returns the name of the move.
 */
string Move::getItsName() const
{
    return itsName;
}

/**
 * Returns the power of the move.
 */
int Move::getItsPower() const
{
    return itsPower;
}

/**
 * Returns the accuracy of the move.
 */
int Move::getItsAccuracy() const
{
    return itsAccuracy;
}

/**
 * Returns the type of the move (e.g., physical or special).
 */
MOVENATURE Move::getItsNature() const
{
    return itsNature;
}

PKTYPE Move::getItsType() const
{
    return itsType;
}

string Move::getItsTextType(int type) const
{
    switch (type) {
    case Grass: return "Plante";
    case Poison: return "Poison";
    case Normal: return "Normal";
    case Bug: return "Insecte";
    case Psychic: return "Psy";
    case Ghost: return "Spectre";
    case Ground: return "Sol";
    case Dragon: return "Dragon";
    case Fairy: return "Fée";
    case Fire: return "Feu";
    case Fighting: return "Combat";
    case Dark: return "Ténèbres";
    case Electric: return "Electrique";
    case Flying: return "Vol";
    case Rock: return "Roche";
    case Steel: return "Acier";
    case Water: return "Eau";
    case Ice: return "Glace";
    default: return "Inconnu";
    }
}


/**
 * Calculates the damage this move will do when used.
 * Implements the standard damage formula from games like Pokémon.
 */
int Move::calculateDamage(int lvl, int atk, int def, bool crit, float typeMultiplier) const {
    int level = lvl;
    int attackStat = atk;
    int defenseStat = def;
    int power = itsPower;

    double critical = crit ? 2.0 : 1.0; // Critical hit doubles the damage

    // Calculate the base damage using a modified version of the Pokémon damage formula
    double baseDamage = ((((level * 0.4 + 2) * attackStat * power) / (defenseStat * 50)) + 2) * critical * typeMultiplier;

    // Ensure damage is at least 1
    return std::max(1, static_cast<int>(baseDamage));
}

