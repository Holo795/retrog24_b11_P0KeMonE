/**
 * @file Battle.h
 * @brief Defines the Battle class which manages combat interactions between players in a Pokémon game.
 */

#ifndef BATTLE_H
#define BATTLE_H

#include <random>

#include "battlehud.h"
#include "player.h"
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
    Player *itsPlayer1;           /**< Pointer to the player participating in the battle. */
    Pokemon *itsOpponent1;        /**< Pointer to the opponent Pokémon in the battle. */
    BattleHUD *itsBattleHUD1;     /**< Pointer to the battle HUD interface. */
    std::mt19937 gen;           /**< Mersenne Twister random number generator. */
    std::vector<Pokemon*> itsBossTeam; /**< Vector of Pokémon pointers representing the boss's team. */

public:
    /**
     * @brief Constructs a Battle instance with provided player, opponent, and HUD.
     * @param itsPlayer1 Pointer to the player.
     * @param opponent1 Pointer to the opponent Pokémon.
     * @param battleHUD1 Pointer to the battle HUD.
     */
    Battle(Player *itsPlayer1, Pokemon *opponent1, BattleHUD *battleHUD1);

    /**
     * @brief Destructor for the Battle class.
     */
    ~Battle();

    /**
     * @brief Executes an attack during a battle.
     * @param move Pointer to the move being used in the attack.
     * @param target Pointer to the Pokémon being targeted.
     */
    void attack(Move *move, Pokemon *target);

    /**
     * @brief Retrieves the boss's team of Pokémon.
     * @return A constant reference to a vector of pointers to Pokémon.
     */
    std::vector<Pokemon*> getBossTeam() const;
};

#endif // BATTLE_H
