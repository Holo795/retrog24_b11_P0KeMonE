#ifndef BATTLEHUD_H
#define BATTLEHUD_H

#include <QGraphicsScene>

class BattleHUD : public QGraphicsScene {
    Q_OBJECT

public:
    BattleHUD(QObject *parent = nullptr);
};

#endif // BATTLEHUD_H
