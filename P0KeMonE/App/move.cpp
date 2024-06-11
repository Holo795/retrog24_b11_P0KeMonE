#include "move.h"

/**
 * @brief Constructor for a Move object.
 * @param itsName Name of the move.
 * @param itsPower Power of the move.
 * @param itsAccuracy Accuracy of the move.
 * @param itsNature Nature of the move (physical or special).
 * @param itsType Type of the move (PKTYPE).
 */
Move::Move(const string &itsName, int itsPower, int itsAccuracy, MOVENATURE itsNature, PKTYPE itsType)
    : itsName(itsName), itsPower(itsPower), itsAccuracy(itsAccuracy), itsNature(itsNature), itsType(itsType) {}

/**
 * @brief Retrieves the name of the move.
 * @return Name of the move.
 */
string Move::getItsName() const {
    return itsName;
}

/**
 * @brief Retrieves the power of the move.
 * @return Power of the move.
 */
int Move::getItsPower() const {
    return itsPower;
}

/**
 * @brief Retrieves the accuracy of the move.
 * @return Accuracy of the move.
 */
int Move::getItsAccuracy() const {
    return itsAccuracy;
}

/**
 * @brief Retrieves the nature of the move.
 * @return Nature of the move.
 */
MOVENATURE Move::getItsNature() const {
    return itsNature;
}

/**
 * @brief Retrieves the type of the move.
 * @return Type of the move.
 */
PKTYPE Move::getItsType() const {
    return itsType;
}

/**
 * @brief Returns the string representation of the type of the move.
 * @param type The type of the move.
 * @return The string representation of the move type.
 */
string Move::getItsTextType(int type) const {
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
 * @brief Calculates the damage this move will do when used.
 * Implements the standard damage formula from games like Pokémon.
 * @param lvl Level of the attacking entity.
 * @param atk Attack stat of the attacking entity.
 * @param def Defense stat of the defending entity.
 * @param crit Whether the attack is a critical hit.
 * @return Calculated damage.
 */
int Move::calculateDamage(int lvl, int atk, int def, bool crit) const {
    int level = lvl;
    int attackStat = atk;
    int defenseStat = def;
    int power = itsPower;

    double critical = crit ? 2.0 : 1.0; // Critical hit doubles the damage

    // Calculate the base damage using a modified version of the Pokémon damage formula
    double baseDamage = (((((level * 0.4 + 2) * attackStat * power) / (defenseStat * 50)) + 2) * critical);

    // Ensure damage is at least 1
    return std::max(1, static_cast<int>(baseDamage));
}
