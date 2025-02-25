/**
 * @file Model.h
 * @author Paulin Paul Achile Lilian
 * @brief Defines the Model class that manages game data and interactions.
 */

#ifndef MODEL_H
#define MODEL_H

#include <QTextStream>
#include <QFile>

#include "data.h"

/**
 * @class Model
 * @brief Manages the main game data, including the map and database interactions.
 *
 * This class loads and provides access to the game map and manages interactions with the game database
 * through an instance of the Data class.
 */
class Model
{
public:
    /**
     * @brief Constructor for the Model class.
     */
    Model();

    /**
     * @brief Destructor for the Model class.
     */
    ~Model();

    /**
     * @brief Loads the game map from a specified file.
     * @param filename Path to the file containing the map data.
     */
    void loadMap(const QString& filename);

    /**
     * @brief Retrieves the game map.
     * @return A constant reference to the map stored as a 2D vector of characters.
     */
    const std::vector<std::vector<int>>& getMap() const;

    /**
     * @brief Retrieves the first team of Pokémon from the database.
     * @return A vector of pointers to the Pokémon in the first team.
     */
    vector<Pokemon*> getPokemonsChoice() const;

    /**
     * @brief Provides access to the game's data handling object.
     * @return Pointer to the Data instance managing database interactions.
     */
    Data * getData();

private:
    Data *data;                         ///< Pointer to the Data class instance for database operations.
    std::vector<std::vector<int>> map;  ///< The map of the game, stored as a 2D character vector.
};

#endif // MODEL_H
