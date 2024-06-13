#include "savemanager.h"

SaveManager::SaveManager(Data *data, int saveInterval, QObject *parent) : QObject(parent)
{
    this->data = data;
    this->saveInterval = saveInterval;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SaveManager::saveGame);
}

void SaveManager::startAutoSave()
{
    if (!timer->isActive()) {
        timer->start(saveInterval);
    }
}

void SaveManager::saveGame(Player player)
{
    saveData sData;
    sData.player_x = player.x();
    sData.player_y = player.y();
    sData.player_lvl = player.getItsLevel();
    sData.team = player.getTeam();

    data->insertSaveData(sData);
}

saveData SaveManager::getSave()
{
    return data->extractSaveData();
}
