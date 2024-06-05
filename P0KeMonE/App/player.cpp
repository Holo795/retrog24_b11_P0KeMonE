#include "player.h"

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    setZValue(2);
    setPixmap(QPixmap(":/player/leftStandPlayer.png").scaled(QSize(11, 16) * scale));

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Player::move);
}

bool Player::checkCollision(QPointF newPos) {
    QList<QGraphicsItem*> items = scene()->items(QRectF(newPos, QSizeF(pixmap().width(), pixmap().height())));
    for (QGraphicsItem* item : items) {
        if (item != this && item->zValue() + 1 == zValue()) {
            QGraphicsRectItem footPlayer(QRectF(newPos.x() + 2, newPos.y() + pixmap().height(), pixmap().width() - 4, 2));
            if (footPlayer.collidesWithItem(item)) {
                return true;
            }
        }
    }
    return false;
}

void Player::startMoving() {
    movementTimer->start(30);
}

void Player::stopMoving() {
    movementTimer->stop();
    activeKeys.clear();
}

void Player::move() {
    if (activeKeys.isEmpty() || activeKeys.size() > 1) return;

    QPointF newPos = pos();

    if (activeKeys.contains(Qt::Key_Left) || activeKeys.contains(Qt::Key_Q)) {
        newPos.setX(newPos.x() - 4);
        if (x() > 0 && !checkCollision(newPos)) {
            setPos(newPos);
            updateDirection("left");
        }
    }

    newPos = pos();

    if (activeKeys.contains(Qt::Key_Right) || activeKeys.contains(Qt::Key_D)) {
        newPos.setX(newPos.x() + 4);
        if (x() + pixmap().width() < scene()->width() && !checkCollision(newPos)) {
            setPos(newPos);
            updateDirection("right");
        }
    }

    newPos = pos();

    if (activeKeys.contains(Qt::Key_Up) || activeKeys.contains(Qt::Key_Z)) {
        newPos.setY(newPos.y() - 4);
        if (y() > 0 && !checkCollision(newPos)) {
            setPos(newPos);
            updateDirection("back");
        }
    }

    newPos = pos();

    if (activeKeys.contains(Qt::Key_Down) || activeKeys.contains(Qt::Key_S)) {
        newPos.setY(newPos.y() + 4);
        if (y() + pixmap().height() < scene()->height() && !checkCollision(newPos)) {
            setPos(newPos);
            updateDirection("front");
        }
    }
}

void Player::updateDirection(const QString &direction) {
    static const QMap<QString, QStringList> pixmapPaths {
        {"left", {":/player/leftStandPlayer.png", ":/player/leftWalkPlayer1.png", ":/player/leftWalkPlayer2.png"}},
        {"right", {":/player/rightStandPlayer.png", ":/player/rightWalkPlayer1.png", ":/player/rightWalkPlayer2.png"}},
        {"back", {":/player/backStandPlayer.png", ":/player/backWalkPlayer1.png", ":/player/backWalkPlayer2.png"}},
        {"front", {":/player/frontStandPlayer.png", ":/player/frontWalkPlayer1.png", ":/player/frontWalkPlayer2.png"}}
    };

    const QStringList &pixmaps = pixmapPaths[direction];
    int step = qRound(direction == "left" || direction == "right" ? x() : y()) % 48;
    int index = step < 16 ? 0 : step < 32 ? 1 : 2;

    setPixmap(QPixmap(pixmaps[index]).scaled(QSize(11, 16) * scale));
}

std::vector<Pokemon*> Player::getTeam() const {
    return itsTeam;
}

void Player::keyPressEvent(QKeyEvent *event) {
    activeKeys.insert(event->key());
    if (!movementTimer->isActive()) {
        startMoving();
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    activeKeys.remove(event->key());
    if (activeKeys.isEmpty()) {
        stopMoving();
    }
}
