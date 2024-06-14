/**
 * @file SaveManager.h
 * @brief Declaration of the SaveManager class.
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
 * @brief Class responsible for managing automatic game saves.
 *
 * This class manages automatic game saves at regular intervals.
 */
class SaveManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the SaveManager class.
     * @param data Pointer to the Data object to be saved.
     * @param player Pointer to the associated Player object.
     * @param parent Pointer to the parent object (default is nullptr).
     */
    SaveManager(Data *data, Player *player, QObject *parent = nullptr);

    /**
     * @brief Starts automatic saving.
     *
     * This method initializes and starts the timer for automatic saving.
     */
    void startAutoSave();

    /**
     * @brief Stops automatic saving.
     *
     * This method stops the timer for automatic saving.
     */
    void stopAutoSave();

    /**
     * @brief Retrieves the save data.
     * @return A saveData object containing the current save data.
     */
    saveData getSave();

public slots:
    /**
     * @brief Saves the game data.
     *
     * This method is called automatically at regular intervals to save the game data.
     */
    void saveGame();

private:
    Data *data; ///< Pointer to the game data to be saved.
    QTimer *timer; ///< Timer for managing automatic saves.
    Player *player; ///< Pointer to the associated Player object.

    int saveInterval = 5 * 60 * 1000; ///< Interval for automatic saving in milliseconds (5 minutes).
};

#endif // SAVEMANAGER_H
