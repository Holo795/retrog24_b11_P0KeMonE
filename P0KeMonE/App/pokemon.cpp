#include "pokemon.h"

Pokemon::Pokemon(int id_pk, const std::string &itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel)
    : id_pk(id_pk), itsName(itsName), itsType(itsType), itsHealth(itsHealth), itsMaxHealth(itsHealth), itsSpeed(itsSpeed), itsAtk(itsAtk),
    itsSpAtk(itsSpAtk), itsDef(itsDef), itsSpDef(itsSpDef), itsLevel(itsLevel)
{
}

/**
 * @brief Determines if the target Pokemon is "dead" or has no health left.
 * @param target Reference to the target Pokemon.
 * @return True if the target Pokemon has no health left, false otherwise.
 */
bool Pokemon::isDead(const Pokemon &target) const
{
    return target.itsHealth <= 0;
}

/**
 * @brief Applies damage to this Pokemon, reducing its health.
 * @param damage Amount of damage to apply.
 */
void Pokemon::takeDamage(int damage)
{
    itsHealth -= damage;
    if (itsHealth < 0) {
        itsHealth = 0; // Ensure health does not drop below zero
    }
}

/**
 * @brief Returns the identifier of this Pokemon.
 * @return Identifier of this Pokemon.
 */
int Pokemon::getId() const
{
    return id_pk;
}

/**
 * @brief Returns the current level of this Pokemon.
 * @return Current level of this Pokemon.
 */
int Pokemon::getLvl() const
{
    return itsLevel;
}

/**
 * @brief Returns the current health of this Pokemon.
 * @return Current health of this Pokemon.
 */
int Pokemon::getHealth() const
{
    return itsHealth;
}

/**
 * @brief Returns the speed statistic of this Pokemon.
 * @return Speed statistic of this Pokemon.
 */
int Pokemon::getSpeed() const
{
    return itsSpeed;
}

/**
 * @brief Returns the attack statistic of this Pokemon.
 * @return Attack statistic of this Pokemon.
 */
int Pokemon::getAtk() const
{
    return itsAtk;
}

/**
 * @brief Returns the special attack statistic of this Pokemon.
 * @return Special attack statistic of this Pokemon.
 */
int Pokemon::getSpAtk() const
{
    return itsSpAtk;
}

/**
 * @brief Returns the defense statistic of this Pokemon.
 * @return Defense statistic of this Pokemon.
 */
int Pokemon::getDef() const
{
    return itsDef;
}

/**
 * @brief Returns the special defense statistic of this Pokemon.
 * @return Special defense statistic of this Pokemon.
 */
int Pokemon::getSpDef() const
{
    return itsSpDef;
}

/**
 * @brief Returns the name of this Pokemon.
 * @return Name of this Pokemon.
 */
std::string Pokemon::getItsName() const
{
    return itsName;
}

/**
 * @brief Returns the maximum health of this Pokemon.
 * @return Maximum health of this Pokemon.
 */
int Pokemon::getItsMaxHealth() const
{
    return itsMaxHealth;
}

/**
 * @brief Upgrades the stats of this Pokemon.
 */
void Pokemon::upgradeStats()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disInt(193, 493);

    std::array<int*, 6> stats = { &itsMaxHealth, &itsSpeed, &itsAtk, &itsSpAtk, &itsDef, &itsSpDef };

    for (int* stat : stats) {
        *stat += *stat / 50 + disInt(gen);
    }

    itsHealth += 10;
}

/**
 * @brief Returns the list of moves this Pokemon can perform.
 * @return List of moves this Pokemon can perform.
 */
QList<Move*> Pokemon::getItsMoves() const
{
    return itsMoves;
}

/**
 * @brief Sets the list of moves this Pokemon can perform.
 * @param newItsMoves New list of moves.
 */
void Pokemon::setItsMoves(const QList<Move*> &newItsMoves)
{
    itsMoves = newItsMoves;
}

/**
 * @brief Returns the type of this Pokemon.
 * @return Type of this Pokemon.
 */
PKTYPE Pokemon::getItsType() const
{
    return itsType;
}
