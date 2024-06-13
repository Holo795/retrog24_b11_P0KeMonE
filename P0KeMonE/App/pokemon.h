/**
 * @file Pokemon.h
 * @author Paulin Paul Achile Lilian
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
    int id_pk;                /**< Identifier of the Pokémon */
    string itsName;           /**< Name of the Pokémon */
    PKTYPE itsType;           /**< Type of the Pokémon */
    int itsHealth;            /**< Current health points of the Pokémon */
    int itsMaxHealth;         /**< Maximum health points of the Pokémon */
    int itsSpeed;             /**< Speed stat of the Pokémon */
    int itsAtk;               /**< Attack stat of the Pokémon */
    int itsSpAtk;             /**< Special attack stat of the Pokémon */
    int itsDef;               /**< Defense stat of the Pokémon */
    int itsSpDef;             /**< Special defense stat of the Pokémon */
    int itsLevel;             /**< Level of the Pokémon */
    QList<Move*> itsMoves;     /**< List of moves or abilities the Pokémon can perform */

public:
    Pokemon(int id_pk, string itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel);

    bool isDead(Pokemon &target);
    void takeDamage(int damage);
    int getId() const;
    int getLvl() const;
    int getHealth() const;
    int getSpeed() const;
    int getAtk() const;
    int getSpAtk() const;
    int getDef() const;
    int getSpDef() const;
    string getItsName() const;
    int getItsMaxHealth() const;
    void upgradeStats();
    QList<Move*> getItsMoves() const;
    void setItsMoves(const QList<Move*> &newItsMoves);
    PKTYPE getItsType() const;
    void setLevel(int newItsLevel);
    Move* getRandMove();
};

#endif // POKEMON_H
