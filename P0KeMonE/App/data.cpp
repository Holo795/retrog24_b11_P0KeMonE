#include "data.h"
#include "pokemon.h"
#include "typeDef.h"

/**
 * Initializes the Data object by setting up and opening a database connection.
 */
Data::Data()
{
    // Establish a connection to the database using SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");

// Set the path to the database file based on the operating system
#if defined _WIN32
    db.setDatabaseName("../../../../P0KeMonE/App/pokemon.sqlite");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
    db.setDatabaseName("../../../../../P0KeMonE/App/pokemon.sqlite");
#endif

    // Open the database and log the status
    if (!db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
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
 * Fetches a random Pokémon from the database and returns a pointer to a newly created Pokémon object.
 */
Pokemon* Data::randompokemon()
{
    qDebug() << "Entering randompokemon()";
    QSqlQuery query;
    if (!query.exec("SELECT P.id, P.name, P.base_experience, P.height, P.weight, P.hp, P.attack, P.defense, P.special_attack, P.special_defense, P.speed, T.id_type FROM pokemon P JOIN type_pk T ON P.id = T.id_pk WHERE T.id_type < 6 ORDER BY RANDOM() LIMIT 1"))
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
        PKTYPE type = static_cast<PKTYPE>(query.value("id_type").toInt());

        Pokemon* pokemon = new Pokemon(id, name.toStdString(), type, hp, speed, attack, special_attack, defense, special_defense, 1);

        qDebug() << "Pokemon created: " << name;

        // Fetch and set the moves for the Pokémon
        QList<Move> moves = getMoves(id);
        if (moves.isEmpty())
        {
            return randompokemon(); // If no moves, fetch another Pokémon
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
 * Fetches and returns a list of moves associated with a given Pokémon ID.
 */
QList<Move> Data::getMoves(int pokemon_id)
{
    qDebug() << "Entering getMoves() with pokemon_id:" << pokemon_id;
    QSqlQuery query;
    QString queryString = "SELECT move.name, move.power, move.accuracy, move.spephy, move.type "
                          "FROM pokemon "
                          "JOIN type ON move.type = type.id"
                          "JOIN move_pk ON pokemon.id = move_pk.id_pk "
                          "JOIN move ON move_pk.id_move = move.id "
                          "WHERE pokemon.id = " + QString::number(pokemon_id);

    if (!query.exec(queryString))
    {
        qDebug() << "Error: query execution failed" << query.lastError();
        return QList<Move>();
    }

    QList<Move> moves;
    while (query.next())
    {
        QString name = query.value("name").toString();
        int power = query.value("power").toInt();
        int accuracy = query.value("accuracy").toInt();
        MOVENATURE nature = query.value("spephy").toString() == "special" ? MOVENATURE::Spéciale : MOVENATURE::Physique;
        PKTYPE type = static_cast<PKTYPE>(query.value("type").toInt());
        Move move(name.toStdString(), power, accuracy, nature, type);
        moves.append(move);
    }
    return moves;
}
