#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Player(QGraphicsItem *parent = nullptr);

private:
    float scale = 1.8;
    bool checkCollision(QPointF newPos);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PLAYER_H
