/**
 * @file Move.h
 * @brief Defines the Move class that represents an attack or move in a game.
 */

#ifndef MOVE_H
#define MOVE_H

#include <string>

#include "typeDef.h"
using namespace std;

/**
 * @class Move
 * @brief Represents a single move or attack in the game.
 *
 * This class stores details about a move including its name, power, accuracy, and type,
 * and provides methods to retrieve these properties and calculate damage.
 */
class Move
{
private:
    string itsName;       ///< Name of the move.
    int itsPower;         ///< Power value of the move, determines damage output.
    int itsAccuracy;      ///< Accuracy percentage of the move.
    MOVENATURE itsType;   ///< Type of the move (e.g., physical, special).
public:
    /**
     * @brief Constructor for a Move object.
     * @param itsName Name of the move.
     * @param itsPower Power of the move.
     * @param itsAccuracy Accuracy of the move.
     * @param itsType Type of the move (physical or special).
     */
    Move(string itsName, int itsPower, int itsAccuracy, MOVENATURE itsType);

    /**
     * @brief Retrieves the name of the move.
     * @return Name of the move.
     */
    string getItsName() const;

    /**
     * @brief Retrieves the power of the move.
     * @return Power of the move.
     */
    int getItsPower() const;

    /**
     * @brief Retrieves the accuracy of the move.
     * @return Accuracy of the move.
     */
    int getItsAccuracy() const;

    /**
     * @brief Retrieves the type of the move.
     * @return Type of the move.
     */
    MOVENATURE getItsType() const;


    /**
     * @brief Calculates the damage inflicted by the move.
     * @param lvl Level of the attacking entity.
     * @param atk Attack stat of the attacking entity.
     * @param def Defense stat of the defending entity.
     * @param crit Whether the attack is a critical hit.
     * @return Calculated damage.
     */
    int calculateDamage(int lvl, int atk, int def, bool crit) const;
};

#endif // MOVE_H
