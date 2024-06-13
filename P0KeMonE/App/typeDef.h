#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <map>
#include <QString>

#include <QBitmap>
#include <QMap>

/**
 * @enum PKTYPE
 * @brief Enumération des types de Pokémon.
 */
enum PKTYPE {
    Grass,      /**< Type Plante */
    Poison,         /**< Type Feu */
    Normal,         /**< Type Eau */
    Bug,        /**< Type Electrique */
    Psychic,       /**< Type Sol */
    Ghost,          /**< Type Vol */
    Ground,          /**< Type Vol */
    Dragon,          /**< Type Vol */
    Fairy,          /**< Type Vol */
    Fire,          /**< Type Vol */
    Fighting,          /**< Type Vol */
    Dark,          /**< Type Vol */
    Electric,          /**< Type Vol */
    Flying,          /**< Type Vol */
    Rock,          /**< Type Vol */
    Steel,          /**< Type Vol */
    Water,          /**< Type Vol */
    Ice,          /**< Type Vol */
};


/**
 * @enum MOVETYPE
 * @brief Enumération des types de mouvements.
 */
enum MOVENATURE {
    Physique, /**< Attaque Physique */
    Spéciale  /**< Attaque Spéciale */
};

extern std::map<int, QString> dialogues; ///< Map of dialogues for the game
extern QMap<int, QBitmap> masks;

extern std::map<PKTYPE, std::map<PKTYPE, float>> typeEffectiveness;



#endif // TYPEDEF_H
