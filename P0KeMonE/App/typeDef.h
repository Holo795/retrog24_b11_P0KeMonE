#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QString>
#include <QBitmap>
#include <QMap>
#include <map>

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
 * @brief Enumeration of Pokémon types.
 */
enum PKTYPE {
    Grass,      /**< Grass type */
    Poison,     /**< Poison type */
    Normal,     /**< Normal type */
    Bug,        /**< Bug type */
    Psychic,    /**< Psychic type */
    Ghost,      /**< Ghost type */
    Ground,     /**< Ground type */
    Dragon,     /**< Dragon type */
    Fairy,      /**< Fairy type */
    Fire,       /**< Fire type */
    Fighting,   /**< Fighting type */
    Dark,       /**< Dark type */
    Electric,   /**< Electric type */
    Flying,     /**< Flying type */
    Rock,       /**< Rock type */
    Steel,      /**< Steel type */
    Water,      /**< Water type */
    Ice         /**< Ice type */
};

/**
 * @enum MOVENATURE
 * @brief Enumeration of move types.
 */
enum MOVENATURE {
    Physique, /**< Physical attack */
    Spéciale  /**< Special attack */
};

extern std::map<int, QString> dialogues;    ///< Map of dialogues for the game
extern QMap<int, QBitmap> masks;            ///< Map of bitmap masks used in the game

extern std::map<PKTYPE, std::map<PKTYPE, float>> typeEffectiveness;



#endif // TYPEDEF_H
