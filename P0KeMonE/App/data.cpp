#include "data.h"
#include "pokemon.h"
#include "typeDef.h"

Data::Data()
{
    db = QSqlDatabase::database();
    db.setDatabaseName(":/database/pokemon.sqlite");
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

    QSqlQuery query;
    query.exec("SELECT P.name, P.base_experience, P.height, P.weight, P.hp, P.attack, P.defense, P.special_attack, P.special_defense, P.speed, T.id_type FROM pokemon P join type_pk T ON P.id = T.id_pk ORDER BY RANDOM() LIMIT 1");

    Pokemon *pokemon = nullptr;



    if (query.next())
    {
        string name = query.value("name").toString().toStdString();
        int hp = query.value("hp").toInt();
        int attack = query.value("attack").toInt();
        int defense = query.value("defense").toInt();
        int special_attack = query.value("special_attack").toInt();
        int special_defense = query.value("special_defense").toInt();
        int speed = query.value("speed").toInt();
        PKTYPE type = static_cast<PKTYPE>(query.value("id_type").toInt());

        pokemon = new Pokemon(name, type, hp, speed, attack, special_attack, defense, special_defense, 1);

        return *pokemon;
    }
    else
    {
        qDebug() << "Error: query failed";
    }


}


