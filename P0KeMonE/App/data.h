#ifndef DATA_H
#define DATA_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>


class Data
{
private:
    QSqlDatabase db;


public:
    Data();
    ~Data();
    void randompokemon();
    void saveGame();
};

#endif // DATA_H
