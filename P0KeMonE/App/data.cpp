#include <QCoreApplication>

#include "data.h"
#include "pokemon.h"
#include "typeDef.h"
#include "QCoreApplication"

/**
 * @brief Constructs a Data object and establishes a connection to the SQLite database.
 *
 * This constructor sets up the database connection using SQLite and opens the database located at the
 * application's directory path with the filename "pokemon.sqlite". It logs the status of the connection
 * attempt to help with debugging.
 */
Data::Data()
{
    // Establish a connection to the database using SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/pokemon_final.sqlite");

    // Open the database and log the status
    if (!db.open())
    {
        // Log an error message if the connection fails
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        // Log a success message if the connection is successful
        qDebug() << "Database: connection ok";
    }
}




/**
 * Closes the database connection when the Data object is destroyed.
 */
Data::~Data()
{
    db.close();
}

/**
 * @brief Fetches a random Pokémon from the database and returns a pointer to a newly created Pokémon object.
 *
 * This function executes a SQL query to select a random Pokémon from the database. It retrieves the Pokémon's
 * attributes and creates a new Pokémon object with those attributes. If no moves are associated with the Pokémon,
 * the function recursively fetches another random Pokémon.
 *
 * @return A pointer to a newly created Pokémon object, or nullptr if the query fails or no results are returned.
 */
Pokemon* Data::randompokemon()
{
    // Log the entry into the function
    qDebug() << "Entering randompokemon()";
    QSqlQuery query;

    // Execute the SQL query to fetch a random Pokémon
    if (!query.exec("SELECT P.id, P.name, P.base_experience, P.height, P.weight, P.hp, P.attack, P.defense, P.special_attack, P.special_defense, P.speed, T.id_type FROM pokemon P JOIN type_pk T ON P.id = T.id_pk WHERE T.id_type < 6 ORDER BY RANDOM() LIMIT 1"))
    {
        qDebug() << "Error: query execution failed" << query.lastError();
        return nullptr;
    }

    // Process the query result
    if (query.next())
    {
        // Create a new Pokémon object from the retrieved data
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        int hp = query.value("hp").toInt();
        int attack = query.value("attack").toInt();
        int defense = query.value("defense").toInt();
        int special_attack = query.value("special_attack").toInt();
        int special_defense = query.value("special_defense").toInt();
        int speed = query.value("speed").toInt();
        PKTYPE type = static_cast<PKTYPE>(query.value("id_type").toInt() - 1);

        Pokemon* pokemon = new Pokemon(id, name.toStdString(), type, hp, speed, attack, special_attack, defense, special_defense, 1);

        qDebug() << "Pokemon created: " << name;

        // Fetch and set the moves for the Pokémon
        QList<Move*> moves = getMoves(id);

        if (moves.isEmpty())
        {
            // If the Pokémon has no moves, fetch another random Pokémon
            delete pokemon;
            return randompokemon();
        }
        pokemon->setItsMoves(moves);
        return pokemon;
    }
    else
    {
        qDebug() << "Error: no results returned from query";
    }
    return nullptr;
}


Pokemon* Data::pokemonById(int pokemonId)
{
    qDebug() << "Entering pokemonById() with ID:" << pokemonId;
    QSqlQuery query;
    query.prepare("SELECT P.id, P.name, P.base_experience, P.height, P.weight, P.hp, P.attack, P.defense, P.special_attack, P.special_defense, P.speed, T.id_type "
                  "FROM pokemon P "
                  "JOIN type_pk T ON P.id = T.id_pk "
                  "WHERE P.id = :id");
    query.bindValue(":id", pokemonId);

    if (!query.exec())
    {
        qDebug() << "Error: query execution failed" << query.lastError();
        return nullptr;
    }

    if (query.next())
    {
        // Create a new Pokémon object from the retrieved data
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        int hp = query.value("hp").toInt();
        int attack = query.value("attack").toInt();
        int defense = query.value("defense").toInt();
        int special_attack = query.value("special_attack").toInt();
        int special_defense = query.value("special_defense").toInt();
        int speed = query.value("speed").toInt();
        PKTYPE type = static_cast<PKTYPE>(query.value("id_type").toInt() - 1);

        Pokemon* pokemon = new Pokemon(id, name.toStdString(), type, hp, speed, attack, special_attack, defense, special_defense, 5);

        qDebug() << "Pokemon created: " << name;

        // Fetch and set the moves for the Pokémon
        QList<Move *> moves = getMoves(id);
        if (moves.isEmpty() || moves.at(0)->getItsPower() == 0)
        {
            // If the Pokémon has no moves, fetch another random Pokémon
            delete pokemon;
        }

        pokemon->setItsMoves(moves);
        return pokemon;
    }
    else
    {
        qDebug() << "Error: no results returned from query";
    }
    return nullptr;
}


/**
 * @brief Fetches and returns a list of moves associated with a given Pokémon ID.
 *
 * This function queries the database to retrieve move information for a specified Pokémon ID.
 * It prepares and executes a SQL query that joins the `move` and `move_pk` tables to get the relevant move details.
 * The results are limited to 4 randomly ordered moves.
 *
 * @param pokemon_id The ID of the Pokémon for which to retrieve moves.
 * @return A QList of pointers to Move objects associated with the given Pokémon ID.
 */
QList<Move*> Data::getMoves(int pokemon_id)
{
    // Log the entry into the function with the provided Pokémon ID
    qDebug() << "Entering getMoves() with pokemon_id:" << pokemon_id;
    QSqlQuery query;

    // Prepare the SQL query to fetch move details
    QString queryString = R"(
        SELECT move.name, move.power, move.accuracy, move.spephy, move.type
        FROM move
        JOIN move_pk ON move.id = move_pk.id_move
        WHERE move_pk.id_pk = :pokemon_id
        ORDER BY RANDOM()
        LIMIT 4
    )";

    query.prepare(queryString);
    query.bindValue(":pokemon_id", pokemon_id);

    // Execute the query and handle potential errors
    if (!query.exec())
    {
        qDebug() << "Error: query execution failed" << query.lastError();
        return QList<Move*>();
    }

    // Process the results and create Move objects
    QList<Move*> moves;
    while (query.next())
    {
        QString name = query.value("name").toString();
        int power = query.value("power").toInt();
        int accuracy = query.value("accuracy").toInt();
        MOVENATURE nature = query.value("spephy").toString() == "special" ? MOVENATURE::Spéciale : MOVENATURE::Physique;
        PKTYPE type = static_cast<PKTYPE>(query.value("type").toInt() - 1);
        Move* move = new Move(name.toStdString(), power, accuracy, nature, type);
        moves.append(move);
    }

    // Return the list of moves
    return moves;
}


