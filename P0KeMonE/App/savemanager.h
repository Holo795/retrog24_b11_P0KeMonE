#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QTimer>
#include <QObject>
#include "data.h"
#include "player.h"
#include "typeDef.h"

class SaveManager : public QObject
{
    Q_OBJECT
public:
    SaveManager(Data *data, Player *player, QObject *parent = nullptr);
    void startAutoSave();
    saveData getSave();


public slots:
    void saveGame();

private:
    Data *data;
    QTimer *timer;
    Player *player;

    int saveInterval = 5 * 60 * 1000;// 5m
};

#endif // SAVEMANAGER_H
