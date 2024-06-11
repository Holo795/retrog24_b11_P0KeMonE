/**
 * @file Data.h
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
    QSqlDatabase db; /**< Instance of the SQLite database */

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
     * @brief Fetches moves associated with a Pokémon by ID.
     * @param pokemon_id The ID of the Pokémon to fetch moves for.
     * @return A QList of Move objects associated with the Pokémon.
     */
    QList<Move*> getMoves(int pokemon_id);

    QSqlDatabase getDb();
};

#endif // DATA_H
