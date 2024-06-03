#include "data.h"
#include "pokemon.h"
#include "typeDef.h"

Data::Data()
{
    // connection to the database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/liliangarcia/Documents/2023-2024/S2/1256/retrog24_b11_P0KeMonE/P0KeMonE/App/pokemon.sqlite");
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



Pokemon Data::randompokemon()
{

    // query to get random pokemon
    QSqlQuery query;
    query.exec("SELECT P.name, P.base_experience, P.height, P.weight, P.hp, P.attack, P.defense, P.special_attack, P.special_defense, P.speed, T.id_type FROM pokemon P join type_pk T ON P.id = T.id_pk ORDER BY RANDOM() LIMIT 1");

    Pokemon *pokemon = nullptr; // init pokemon pointer null



    if (query.next())
    {
        // get pokemon data from query
        string name = query.value("name").toString().toStdString();
        int hp = query.value("hp").toInt();
        int attack = query.value("attack").toInt();
        int defense = query.value("defense").toInt();
        int special_attack = query.value("special_attack").toInt();
        int special_defense = query.value("special_defense").toInt();
        int speed = query.value("speed").toInt();
        PKTYPE type = static_cast<PKTYPE>(query.value("id_type").toInt());

        //cretation of the pokemon object
        pokemon = new Pokemon(name, type, hp, speed, attack, special_attack, defense, special_defense, 1);

        qDebug() << "Pokemon: " << name.c_str() << " Type: " << type << " HP: " << hp << " Speed: " << speed << " Attack: " << attack << " Special Attack: " << special_attack << " Defense: " << defense << " Special Defense: " << special_defense;

        // return the pokemon object
        return *pokemon;
    }
    else
    {
        // message if query failed
        qDebug() << "Error: query failed";
    }

    // return the pokemon object
    return *pokemon;


}






