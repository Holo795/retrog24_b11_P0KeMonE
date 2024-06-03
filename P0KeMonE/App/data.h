/**
 * @file data.h
 * @brief Définition de la classe Data pour la gestion des opérations de base de données liées aux Pokémon.
 */

#ifndef DATA_H
#define DATA_H

#include "pokemon.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QSqlError>

/**
 * @class Data
 * @brief La classe Data gère les opérations de base de données pour les Pokémon.
 */
class Data
{
private:
    QSqlDatabase db; /**< Instance de la base de données SQLite */

public:
    /**
     * @brief Constructeur de la classe Data.
     * Initialise et ouvre la connexion à la base de données.
     */
    Data();

    /**
     * @brief Destructeur de la classe Data.
     * Ferme la connexion à la base de données.
     */
    ~Data();

    /**
     * @brief Récupère un Pokémon aléatoire depuis la base de données.
     * @return Un objet Pokémon initialisé avec les données récupérées.
     */
    Pokemon randompokemon();
};

#endif // DATA_H
