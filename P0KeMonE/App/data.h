/**
 * @file Data.h
 * @author Paulin Paul Achile Lilian
 * @brief Definition of the Data class for managing database operations related to Pokémon.
 */

#ifndef DATA_H
#define DATA_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QSqlError>

#include <QCoreApplication>

#include "pokemon.h"

/**
 * @class Data
 * @brief Manages database operations for Pokémon.
 *
 * This class encapsulates all database interactions in a Pokémon game, including retrieving and
 * storing Pokémon and their moves.
 */
class Data
{
private:
    QSqlDatabase db;    /**< Instance of the SQLite database */

public:
    /**
     * @brief Constructor for Data class.
     * Initializes and opens the database connection.
     */
    Data();

    /**
     * @brief Destructor for Data class.
     * Closes the database connection.
     */
    ~Data();

    /**
     * @brief Retrieves a random Pokémon from the database.
     * @return A new Pokémon object initialized with the fetched data.
     */
    Pokemon * randompokemon();

    /**
     * @brief Retrieves a Pokémon from the database by ID.
     * @param pokemonId The ID of the Pokémon to fetch.
     * @param level The level of the Pokémon to fetch.
     * @return A new Pokémon object initialized with the fetched data.
     */
    Pokemon* pokemonById(int pokemonId, int level);

    /**
     * @brief Fetches moves associated with a Pokémon by ID.
     * @param pokemon_id The ID of the Pokémon to fetch moves for.
     * @return A QList of Move objects associated with the Pokémon.
     */
    QList<Move*> getMoves(int pokemon_id);

    /**
     * @brief Extracts saved game data from the database.
     * @return The extracted saveData object containing game state information.
     */
    saveData extractSaveData();

    /**
     * @brief Inserts saved game data into the database.
     * @param data The saveData object containing game state information to be inserted.
     */
    void insertSaveData(saveData data);

    /**
     * @brief Clears all saved game data from the database.
     */
    void clearSaveData();
};

#endif // DATA_H
