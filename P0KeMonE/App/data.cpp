#include "data.h"
#include "pokemon.h"
#include "typeDef.h"

Data::Data()
{
    // connection to the database
    db = QSqlDatabase::addDatabase("QSQLITE");

#if defined _WIN32
    db.setDatabaseName("../../../../P0KeMonE/App/pokemon.sqlite");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
    db.setDatabaseName("../../../../../P0KeMonE/App/pokemon.sqlite");
#endif



    // if the database is not open, we open it
    if (!db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

Data::~Data()
{

    db.close(); // database closed

}



Pokemon* Data::randompokemon()
{
    qDebug() << "Entering randompokemon()";

    // query to get random pokemon
    QSqlQuery query;
    if (!query.exec("SELECT P.id, P.name, P.base_experience, P.height, P.weight, P.hp, P.attack, P.defense, P.special_attack, P.special_defense, P.speed, T.id_type FROM pokemon P JOIN type_pk T ON P.id = T.id_pk WHERE T.id_type < 6 ORDER BY RANDOM() LIMIT 1"))
    {
        qDebug() << "Error: query execution failed" << query.lastError();
        return nullptr;
    }

    Pokemon* pokemon = nullptr; // init pokemon pointer null

    if (query.next())
    {
        // get pokemon data from query
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        int hp = query.value("hp").toInt();
        int attack = query.value("attack").toInt();
        int defense = query.value("defense").toInt();
        int special_attack = query.value("special_attack").toInt();
        int special_defense = query.value("special_defense").toInt();
        int speed = query.value("speed").toInt();
        PKTYPE type = static_cast<PKTYPE>(query.value("id_type").toInt());

        //cretation of the pokemon object
        pokemon = new Pokemon(id, name.toStdString(), type, hp, speed, attack, special_attack, defense, special_defense, 1);

        qDebug() << "Pokemon created: " << name;


        // Call to getMoves
        QList<Move> moves = getMoves(id);
        if (moves.size() == 0) {
            return randompokemon();

        }
        pokemon->setItsMoves(moves);

        // return the pokemon object
        return pokemon;
    }
    else
    {
        // message if query failed
        qDebug() << "Error: no results returned from query";
    }

    // return the pokemon object
    return pokemon;
}


QList<Move> Data::getMoves(int pokemon_id)
{
    qDebug() << "Entering getMoves() with pokemon_id:" << pokemon_id;

    // Préparation de la requête SQL pour obtenir les mouvements d'un Pokémon
    QSqlQuery query;
    QString queryString = "SELECT move.name, move.power, move.accuracy, move.spephy "
                          "FROM pokemon "
                          "JOIN move_pk ON pokemon.id = move_pk.id_pk "
                          "JOIN move ON move_pk.id_move = move.id "
                          "WHERE pokemon.id = " + QString::number(pokemon_id);

    // Exécution de la requête SQL
    if (!query.exec(queryString))
    {
        // Si la requête échoue, affichez l'erreur
        qDebug() << "Error: query execution failed" << query.lastError();
        return QList<Move>();
    }

    QList<Move> moves; // Liste des mouvements

    // Parcours des résultats de la requête
    while (query.next())
    {
        // Récupération des données du mouvement depuis la requête
        QString name = query.value("name").toString();
        int power = query.value("power").toInt();
        int accuracy = query.value("accuracy").toInt();
        MOVENATURE nature = query.value("spephy").toString() == "special" ? MOVENATURE::Spéciale : MOVENATURE::Physique;

        qDebug() << "Move: " << name; // Affichage du nom du mouvement

        // Création de l'objet Move
        Move move(name.toStdString(), power, accuracy, nature);

        // Ajout du mouvement à la liste
        moves.append(move);
    }

    // Retourne la liste des mouvements
    return moves;
}
