/**
 * @file Pokemon.h
 * @brief Declaration of the Pokemon class, which encapsulates properties and behaviors of a Pokémon in the game.
 */

#ifndef POKEMON_H
#define POKEMON_H

#include <QList>

#include "move.h"
#include "typeDef.h"

using namespace std;

/**
 * @class Pokemon
 * @brief Represents a Pokémon with its characteristics and abilities.
 *
 * This class manages all aspects related to a Pokémon's state, including health, attacks, and other stats.
 */
class Pokemon
{
private:
    QList<Move*> itsMoves;    /**< List of moves or abilities the Pokémon can perform */
    string itsName;           /**< Name of the Pokémon */
    PKTYPE itsType;           /**< Type of the Pokémon */
    int id_pk;                /**< Identifier of the Pokémon */
    int itsHealth;            /**< Current health points of the Pokémon */
    int itsMaxHealth;         /**< Maximum health points of the Pokémon */
    int itsSpeed;             /**< Speed stat of the Pokémon */
    int itsAtk;               /**< Attack stat of the Pokémon */
    int itsSpAtk;             /**< Special attack stat of the Pokémon */
    int itsDef;               /**< Defense stat of the Pokémon */
    int itsSpDef;             /**< Special defense stat of the Pokémon */
    int itsLevel;             /**< Level of the Pokémon */

public:
    /**
     * @brief Constructs a Pokémon object with specified attributes.
     * @param id_pk Identifier of the Pokémon.
     * @param itsName Name of the Pokémon.
     * @param itsType Type of the Pokémon.
     * @param itsHealth Initial health points of the Pokémon.
     * @param itsSpeed Speed stat of the Pokémon.
     * @param itsAtk Attack stat of the Pokémon.
     * @param itsSpAtk Special attack stat of the Pokémon.
     * @param itsDef Defense stat of the Pokémon.
     * @param itsSpDef Special defense stat of the Pokémon.
     * @param itsLevel Level of the Pokémon.
     */
    Pokemon(int id_pk, string itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel);

    /**
     * @brief Checks if the Pokémon is dead.
     * @param target Reference to the target Pokémon.
     * @return True if the Pokémon is dead, false otherwise.
     */
    bool isDead(Pokemon &target);

    /**
     * @brief Reduces the Pokémon's health by a specified amount of damage.
     * @param damage Amount of damage to take.
     */
    void takeDamage(int damage);

    /**
     * @brief Retrieves the Pokémon's identifier.
     * @return The Pokémon's identifier.
     */
    int getId() const;

    /**
     * @brief Retrieves the Pokémon's level.
     * @return The Pokémon's level.
     */
    int getLvl() const;

    /**
     * @brief Retrieves the Pokémon's current health.
     * @return The Pokémon's current health.
     */
    int getHealth() const;

    /**
     * @brief Retrieves the Pokémon's speed stat.
     * @return The Pokémon's speed stat.
     */
    int getSpeed() const;

    /**
     * @brief Retrieves the Pokémon's attack stat.
     * @return The Pokémon's attack stat.
     */
    int getAtk() const;

    /**
     * @brief Retrieves the Pokémon's special attack stat.
     * @return The Pokémon's special attack stat.
     */
    int getSpAtk() const;

    /**
     * @brief Retrieves the Pokémon's defense stat.
     * @return The Pokémon's defense stat.
     */
    int getDef() const;

    /**
     * @brief Retrieves the Pokémon's special defense stat.
     * @return The Pokémon's special defense stat.
     */
    int getSpDef() const;

    /**
     * @brief Retrieves the Pokémon's name.
     * @return The Pokémon's name.
     */
    string getItsName() const;

    /**
     * @brief Retrieves the Pokémon's maximum health.
     * @return The Pokémon's maximum health.
     */
    int getItsMaxHealth() const;

    /**
     * @brief Upgrades the Pokémon's stats.
     */
    void upgradeStats();

    /**
     * @brief Retrieves the list of the Pokémon's moves.
     * @return A list of the Pokémon's moves.
     */
    QList<Move*> getItsMoves() const;

    /**
     * @brief Sets the Pokémon's moves.
     * @param newItsMoves The new list of moves to set.
     */
    void setItsMoves(const QList<Move*> &newItsMoves);

    /**
     * @brief Retrieves the Pokémon's type.
     * @return The Pokémon's type.
     */
    PKTYPE getItsType() const;

    /**
     * @brief Sets the Pokémon's level.
     * @param newItsLevel The new level to set.
     */
    void setLevel(int newItsLevel);

    /**
     * @brief Retrieves a random move from the Pokémon's move list.
     * @return A pointer to the selected move.
     */
    Move* getRandMove();
};

#endif // POKEMON_H
