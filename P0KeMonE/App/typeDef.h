#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <map>
#include <QString>

#include <QBitmap>
#include <QMap>

class Pokemon;
struct saveData {
    bool empty = false;
    int player_x;
    int player_y;
    int player_lvl;
    std::vector<Pokemon*> team;
};
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

#endif // TYPEDEF_H
