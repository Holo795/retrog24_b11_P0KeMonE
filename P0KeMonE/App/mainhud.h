#ifndef MAINHUD_H
#define MAINHUD_H

#include <QGraphicsScene>

class MainHUD : public QGraphicsScene
{
public:
    MainHUD(QObject *parent = nullptr);

    void displayMainMenu();
};

#endif // MAINHUD_H
