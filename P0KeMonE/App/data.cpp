#include "data.h"

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

void Data::randompokemon()
{

    QSqlQuery query;
    query.prepare("SELECT * FROM pokemon WHERE id = :id");
    query.bindValue(":id", 1);
    query.exec();
    if (query.next())
    {
        qDebug() << query.value(0).toInt() << query.value(1).toString() << query.value(2).toString();
    }
    else
    {
        qDebug() << "Error: query failed";
    }


}

void Data::saveGame()
{

}
