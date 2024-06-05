#ifndef GAMEOVERHUD_H
#define GAMEOVERHUD_H

#include <QGraphicsScene>

class GameOverHUD : public QGraphicsScene
{
    Q_OBJECT
public:
    GameOverHUD(QObject *parent = nullptr);
};

#endif // GAMEOVERHUD_H
