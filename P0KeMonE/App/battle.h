/**
 * @file Battle.h
 * @author Paulin Paul Achile Lilian
 * @brief Defines the Battle class which manages combat interactions between players in a Pokémon game.
 */

#ifndef BATTLE_H
#define BATTLE_H

#include <random>
#include <QTimer>

#include "battlehud.h"
#include "pokemon.h"

/**
 * @class Battle
 * @brief Manages the mechanics of a battle between a player and an opponent in a Pokémon game.
 *
 * This class encapsulates all the functionalities for a Pokémon battle, including initiating attacks
 * and updating the battle HUD.
 */
class Battle
{
private:
    std::mt19937 gen;           /**< Mersenne Twister random number generator. */
    Pokemon *itsOpponent1;      /**< Pointer to the player's Pokémon in the battle. */
    Pokemon *itsOpponent2;      /**< Pointer to the opponent Pokémon in the battle. */
    BattleHUD *itsBattleHUD;    /**< Pointer to the battle HUD interface. */

public:
    /**
     * @brief Constructs a Battle instance with provided player, opponent, and HUD.
     * @param opponent1 Pointer to the player Pokémon.
     * @param opponent2 Pointer to the opponent Pokémon.
     * @param battleHUD1 Pointer to the battle HUD.
     */
    Battle(Pokemon *opponent1, Pokemon *opponent2, BattleHUD *battleHUD);

    /**
     * @brief Destructor for the Battle class.
     */
    ~Battle();

    void showEffectivenessText(Pokemon *attacker, float typeMultiplier);

    /**
     * @brief Executes an attack during a battle.
     * @param move Pointer to the move being used in the attack.
     * @param target Pointer to the Pokémon being targeted.
     */
    void attack(Move *move, Pokemon *target);

};

#endif // BATTLE_H
