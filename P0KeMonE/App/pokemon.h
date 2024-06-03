/**
 * @file pokemon.h
 * @brief Déclaration de la classe Pokemon.
 */

#ifndef POKEMON_H
#define POKEMON_H

#include "move.h"
#include <QList>
#include <iostream>
using namespace std;

/**
 * @enum PKTYPE
 * @brief Enumération des types de Pokémon.
 */
enum PKTYPE {
    Plante,      /**< Type Plante */
    Feu,         /**< Type Feu */
    Eau,         /**< Type Eau */
    Electrique,  /**< Type Electrique */
    Glace,       /**< Type Glace */
    Vol          /**< Type Vol */
};

/**
 * @class Pokemon
 * @brief Représente un Pokémon avec ses caractéristiques et ses capacités.
 */
class Pokemon
{
private:
    string itsName;           /**< Nom du Pokémon */
    PKTYPE itsType;           /**< Type du Pokémon */
    int itsHealth;            /**< Points de vie du Pokémon */
    int itsSpeed;             /**< Vitesse du Pokémon */
    int itsAtk;               /**< Attaque du Pokémon */
    int itsSpAtk;             /**< Attaque spéciale du Pokémon */
    int itsDef;               /**< Défense du Pokémon */
    int itsSpDef;             /**< Défense spéciale du Pokémon */
    int itsLevel;             /**< Niveau du Pokémon */
    QList<Move> itsMoves;     /**< Liste des capacités (moves) du Pokémon */

public:
    /**
     * @brief Constructeur de la classe Pokemon.
     * @param itsName Nom du Pokémon.
     * @param itsType Type du Pokémon.
     * @param itsHealth Points de vie initiaux du Pokémon.
     * @param itsSpeed Vitesse initiale du Pokémon.
     * @param itsAtk Attaque initiale du Pokémon.
     * @param itsSpAtk Attaque spéciale initiale du Pokémon.
     * @param itsDef Défense initiale du Pokémon.
     * @param itsSpDef Défense spéciale initiale du Pokémon.
     * @param itsLevel Niveau initial du Pokémon.
     */
    Pokemon(string itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel);

    /**
     * @brief Destructeur de la classe Pokemon.
     */
    ~Pokemon();

    /**
     * @brief Vérifie si le Pokémon cible est KO (mort).
     * @param target Référence vers le Pokémon cible.
     * @return true si le Pokémon cible est KO, false sinon.
     */
    bool isDead(Pokemon &target);

    /**
     * @brief Applique des dégâts au Pokémon.
     * @param damage Quantité de dégâts à appliquer.
     */
    void takeDamage(int damage);

    /**
     * @brief Attaque un Pokémon cible avec une capacité spécifique.
     * @param target Référence vers le Pokémon cible.
     * @param move Capacité utilisée pour l'attaque.
     */
    void attack(Pokemon &target, Move move);
};

#endif // POKEMON_H
