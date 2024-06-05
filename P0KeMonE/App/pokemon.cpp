#include "pokemon.h"

/**
 * Constructs a Pokemon with specified attributes.
 */
Pokemon::Pokemon(int id_pk, string itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel)
    : id_pk(id_pk), itsName(itsName), itsType(itsType), itsHealth(itsHealth), itsMaxHealth(itsHealth), itsSpeed(itsSpeed), itsAtk(itsAtk),
    itsSpAtk(itsSpAtk), itsDef(itsDef), itsSpDef(itsSpDef), itsLevel(itsLevel)
{
}

/**
 * Destructor for Pokemon, potentially useful for managing resources if Pokemon instances manage dynamic resources.
 */
Pokemon::~Pokemon()
{
}

/**
 * Determines if the target Pokemon is "dead" or has no health left.
 */
bool Pokemon::isDead(Pokemon &target)
{
    return target.itsHealth <= 0;
}

/**
 * Applies damage to this Pokemon, reducing its health.
 */
void Pokemon::takeDamage(int damage)
{
    itsHealth -= damage;
    if (itsHealth < 0) {
        itsHealth = 0; // Ensure health does not drop below zero
    }
}

/**
 * Returns the current level of this Pokemon.
 */
int Pokemon::getLvl() const
{
    return itsLevel;
}

/**
 * Returns the current health of this Pokemon.
 */
int Pokemon::getHealth() const
{
    return itsHealth;
}

/**
 * Returns the speed statistic of this Pokemon.
 */
int Pokemon::getSpeed() const
{
    return itsSpeed;
}

/**
 * Returns the attack statistic of this Pokemon.
 */
int Pokemon::getAtk() const
{
    return itsAtk;
}

/**
 * Returns the special attack statistic of this Pokemon.
 */
int Pokemon::getSpAtk() const
{
    return itsSpAtk;
}

/**
 * Returns the defense statistic of this Pokemon.
 */
int Pokemon::getDef() const
{
    return itsDef;
}

/**
 * Returns the special defense statistic of this Pokemon.
 */
int Pokemon::getSpDef() const
{
    return itsSpDef;
}

/**
 * Returns the identifier of this Pokemon.
 */
int Pokemon::getId() const
{
    return id_pk;
}

/**
 * Returns the name of this Pokemon.
 */
string Pokemon::getItsName() const
{
    return itsName;
}

/**
 * Returns the maximum health of this Pokemon.
 */
int Pokemon::getItsMaxHealth() const
{
    return itsMaxHealth;
}

/**
 * Returns the list of moves this Pokemon can perform.
 */
QList<Move> Pokemon::getItsMoves() const
{
    return itsMoves;
}

/**
 * Sets the list of moves this Pokemon can perform.
 */
void Pokemon::setItsMoves(const QList<Move> &newItsMoves)
{
    itsMoves = newItsMoves;
}
