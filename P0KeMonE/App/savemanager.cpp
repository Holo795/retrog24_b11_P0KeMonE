#include "savemanager.h"

SaveManager::SaveManager(Data *data, Player *player, QObject *parent) : QObject(parent)
{
    this->data = data;
    this->player = player;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SaveManager::saveGame);
}

void SaveManager::startAutoSave()
{
    if (!timer->isActive() && player != nullptr) {
        qDebug () << "Starting auto save...";
        timer->start(saveInterval);
    }
}

void SaveManager::saveGame()
{

    if (player == nullptr) {
        return;
    }

    qDebug () << "Saving game...";

    saveData sData;
    sData.player_x = player->x();
    sData.player_y = player->y();
    sData.player_lvl = player->getItsLevel();
    sData.team = player->getTeam();

    data->insertSaveData(sData);
}

saveData SaveManager::getSave()
{
    return data->extractSaveData();
}
