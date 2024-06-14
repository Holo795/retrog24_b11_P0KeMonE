/**
 * @file SaveManager.h
 * @brief Déclaration de la classe SaveManager.
 */

#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QTimer>
#include <QObject>
#include "data.h"
#include "player.h"
#include "typeDef.h"

/**
 * @class SaveManager
 * @brief Classe responsable de la gestion des sauvegardes automatiques.
 *
 * Cette classe permet de gérer les sauvegardes automatiques des données du jeu
 * à intervalles réguliers.
 */
class SaveManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe SaveManager.
     * @param data Pointeur vers l'objet Data à sauvegarder.
     * @param player Pointeur vers l'objet Player associé.
     * @param parent Pointeur vers l'objet parent (par défaut nullptr).
     */
    SaveManager(Data *data, Player *player, QObject *parent = nullptr);

    /**
     * @brief Démarre la sauvegarde automatique.
     *
     * Cette méthode initialise et démarre le timer pour la sauvegarde automatique.
     */
    void startAutoSave();

    /**
     * @brief Arrête la sauvegarde automatique.
     *
     * Cette méthode arrête le timer pour la sauvegarde automatique.
     */
    void stopAutoSave();

    /**
     * @brief Récupère les données de sauvegarde.
     * @return Un objet saveData contenant les données de sauvegarde actuelles.
     */
    saveData getSave();

public slots:
    /**
     * @brief Sauvegarde les données du jeu.
     *
     * Cette méthode est appelée automatiquement à intervalles réguliers pour
     * sauvegarder les données du jeu.
     */
    void saveGame();

private:
    Data *data; ///< Pointeur vers les données du jeu à sauvegarder.
    QTimer *timer; ///< Timer pour la gestion des sauvegardes automatiques.
    Player *player; ///< Pointeur vers l'objet Player associé.

    int saveInterval = 5 * 60 * 1000; ///< Intervalle de sauvegarde automatique en millisecondes (5 minutes).
};

#endif // SAVEMANAGER_H
