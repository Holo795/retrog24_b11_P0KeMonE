/**
 * @file Pokemon.h
 * @brief Declaration of the Pokemon class, which encapsulates properties and behaviors of a Pokémon in the game.
 */

#ifndef POKEMON_H
#define POKEMON_H

#include <QList>
#include <random>
#include <array>
#include "move.h"
#include "typeDef.h"

/**
 * @class Pokemon
 * @brief Represents a Pokémon with its characteristics and abilities.
 *
 * This class manages all aspects related to a Pokémon's state, including health, attacks, and other stats.
 */
class Pokemon
{
private:
    int id_pk;                /**< Identifier of the Pokémon */
    std::string itsName;      /**< Name of the Pokémon */
    PKTYPE itsType;           /**< Type of the Pokémon */
    int itsHealth;            /**< Current health points of the Pokémon */
    int itsMaxHealth;         /**< Maximum health points of the Pokémon */
    int itsSpeed;             /**< Speed stat of the Pokémon */
    int itsAtk;               /**< Attack stat of the Pokémon */
    int itsSpAtk;             /**< Special attack stat of the Pokémon */
    int itsDef;               /**< Defense stat of the Pokémon */
    int itsSpDef;             /**< Special defense stat of the Pokémon */
    int itsLevel;             /**< Level of the Pokémon */
    QList<Move*> itsMoves;    /**< List of moves or abilities the Pokémon can perform */

public:
    /**
     * @brief Constructs a Pokemon with specified attributes.
     * @param id_pk Identifier of the Pokémon.
     * @param itsName Name of the Pokémon.
     * @param itsType Type of the Pokémon.
     * @param itsHealth Initial health of the Pokémon.
     * @param itsSpeed Speed stat of the Pokémon.
     * @param itsAtk Attack stat of the Pokémon.
     * @param itsSpAtk Special attack stat of the Pokémon.
     * @param itsDef Defense stat of the Pokémon.
     * @param itsSpDef Special defense stat of the Pokémon.
     * @param itsLevel Level of the Pokémon.
     */
    Pokemon(int id_pk, const std::string &itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel);

    /**
     * @brief Determines if the target Pokemon is "dead" or has no health left.
     * @param target Reference to the target Pokemon.
     * @return True if the target Pokemon has no health left, false otherwise.
     */
    bool isDead(const Pokemon &target) const;

    /**
     * @brief Applies damage to this Pokemon, reducing its health.
     * @param damage Amount of damage to apply.
     */
    void takeDamage(int damage);

    /**
     * @brief Returns the identifier of this Pokemon.
     * @return Identifier of this Pokemon.
     */
    int getId() const;

    /**
     * @brief Returns the current level of this Pokemon.
     * @return Current level of this Pokemon.
     */
    int getLvl() const;

    /**
     * @brief Returns the current health of this Pokemon.
     * @return Current health of this Pokemon.
     */
    int getHealth() const;

    /**
     * @brief Returns the speed statistic of this Pokemon.
     * @return Speed statistic of this Pokemon.
     */
    int getSpeed() const;

    /**
     * @brief Returns the attack statistic of this Pokemon.
     * @return Attack statistic of this Pokemon.
     */
    int getAtk() const;

    /**
     * @brief Returns the special attack statistic of this Pokemon.
     * @return Special attack statistic of this Pokemon.
     */
    int getSpAtk() const;

    /**
     * @brief Returns the defense statistic of this Pokemon.
     * @return Defense statistic of this Pokemon.
     */
    int getDef() const;

    /**
     * @brief Returns the special defense statistic of this Pokemon.
     * @return Special defense statistic of this Pokemon.
     */
    int getSpDef() const;

    /**
     * @brief Returns the name of this Pokemon.
     * @return Name of this Pokemon.
     */
    std::string getItsName() const;

    /**
     * @brief Returns the maximum health of this Pokemon.
     * @return Maximum health of this Pokemon.
     */
    int getItsMaxHealth() const;

    /**
     * @brief Upgrades the stats of this Pokemon.
     */
    void upgradeStats();

    /**
     * @brief Returns the list of moves this Pokemon can perform.
     * @return List of moves this Pokemon can perform.
     */
    QList<Move*> getItsMoves() const;

    /**
     * @brief Sets the list of moves this Pokemon can perform.
     * @param newItsMoves New list of moves.
     */
    void setItsMoves(const QList<Move*> &newItsMoves);

    /**
     * @brief Returns the type of this Pokemon.
     * @return Type of this Pokemon.
     */
    PKTYPE getItsType() const;
};

#endif // POKEMON_H
