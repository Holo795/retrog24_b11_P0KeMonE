#include "Player.h"

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/player/frontStandPlayer.png").scaled(QSize(11, 16)));  // Assurez-vous de mettre le bon chemin vers l'image du joueur
}

void Player::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        if (x() > 0) // Bordure gauche
        {
            setPos(x() - 4, y());
            if(qRound(x())% 48 >= 16 && qRound(x()) % 48 < 32) {
                setPixmap(QPixmap(":/player/leftWalkPlayer1.png").scaled(QSize(10, 16)));
            } else if(qRound(x()) % 48 >= 32) {
                setPixmap(QPixmap(":/player/leftWalkPlayer2.png").scaled(QSize(11, 16)));
            } else {
                setPixmap(QPixmap(":/player/leftStandPlayer.png").scaled(QSize(11, 16)));
            }
        }
        break;
    case Qt::Key_Right:
        if (x() + pixmap().width() < scene()->width()) // Bordure droite
        {
            setPos(x() + 4, y());
            if(qRound(x()) % 48 >= 16 && qRound(x()) % 48 < 32) {
                setPixmap(QPixmap(":/player/rightWalkPlayer1.png").scaled(QSize(11, 16)));
            } else if(qRound(x()) % 48 >= 32) {
                setPixmap(QPixmap(":/player/rightWalkPlayer2.png").scaled(QSize(11, 16)));
            } else {
                setPixmap(QPixmap(":/player/rightStandPlayer.png").scaled(QSize(11, 16)));
            }
        }
        break;
    case Qt::Key_Up:
        if (y() > 0)  // Bordure supérieure
        {
            setPos(x(), y() - 4);
            if(qRound(y()) % 48 >= 16 && qRound(y()) % 48 < 32) {
                setPixmap(QPixmap(":/player/backWalkPlayer1.png").scaled(QSize(11, 16)));
            } else if(qRound(y()) % 48 >= 32) {
                setPixmap(QPixmap(":/player/backWalkPlayer2.png").scaled(QSize(11, 16)));
            } else {
                setPixmap(QPixmap(":/player/backStandPlayer.png").scaled(QSize(11, 16)));
            }
        }
        break;
    case Qt::Key_Down:
        if (y() + pixmap().height() < scene()->height())  // Bordure inférieure
        {
            setPos(x(), y() + 4);
            if(qRound(y()) % 48 >= 16 && qRound(y()) % 48 < 32) {
                setPixmap(QPixmap(":/player/frontWalkPlayer1.png").scaled(QSize(11, 16)));
            } else if(qRound(y()) % 48 >= 32) {
                setPixmap(QPixmap(":/player/frontWalkPlayer2.png").scaled(QSize(11, 16)));
            } else {
                setPixmap(QPixmap(":/player/frontStandPlayer.png").scaled(QSize(11, 16)));
            }
        }
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {

}
