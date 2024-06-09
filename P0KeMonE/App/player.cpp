#include "player.h"
#include "global.h" // Inclusion de la déclaration de la map de masques

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    setZValue(3);
    setPixmap(QPixmap(":/sprites/player_sprites/rightStandPlayer.png").scaled(QSize(11, 16) * scale));
    setTransformationMode(Qt::SmoothTransformation);

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Player::move);
}

Player::~Player() {
    delete movementTimer;
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

void Player::startMoving() {
    movementTimer->start(30);
}

void Player::stopMoving() {
    movementTimer->stop();
    activeKeys.clear();
}

void Player::addPokemon(Pokemon *pokemon) {
    itsTeam.push_back(pokemon);
}

bool Player::checkCollision(QPointF newPos) {
    // Définir la zone de collision du joueur
    QRectF footPlayerRect(newPos.x() + 2, newPos.y() + pixmap().height() - 2, pixmap().width() - 4, 2);

    QList<QGraphicsItem*> items = scene()->items(QRectF(newPos, QSizeF(pixmap().width(), pixmap().height())));
    for (QGraphicsItem* item : items) {
        if (item != this && item->zValue() + 1 == zValue()) {
            int tileId = item->data(0).toInt();
            if (masks.contains(tileId)) {
                QBitmap itemMask = masks[tileId];

                // Convertir les coordonnées du joueur dans le système de coordonnées de l'item
                QPointF itemTopLeft = item->pos();
                QRectF itemRect = QRectF(itemTopLeft, itemMask.size());

                // Vérifier la collision pixel par pixel
                for (int x = 0; x < footPlayerRect.width(); ++x) {
                    for (int y = 0; y < footPlayerRect.height(); ++y) {
                        QPointF playerPixelPos = QPointF(footPlayerRect.x() + x, footPlayerRect.y() + y);
                        QPoint maskPos = playerPixelPos.toPoint() - itemTopLeft.toPoint();

                        if (maskPos.x() >= 0 && maskPos.y() >= 0 &&
                            maskPos.x() < itemMask.width() && maskPos.y() < itemMask.height()) {
                            if (itemMask.toImage().pixelColor(maskPos) != Qt::transparent) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}


void Player::move() {
    if (activeKeys.isEmpty() || activeKeys.size() > 1) return;

    QPointF newPos = pos();

    if (activeKeys.contains(Qt::Key_Left) || activeKeys.contains(Qt::Key_Q)) {
        newPos.setX(newPos.x() - 4);
        if (x() > 0 && !checkCollision(newPos)) {
            setPos(newPos);
            updateSprite("left");
        }
    }

    newPos = pos();

    if (activeKeys.contains(Qt::Key_Right) || activeKeys.contains(Qt::Key_D)) {
        newPos.setX(newPos.x() + 4);
        if (x() + pixmap().width() < scene()->width() && !checkCollision(newPos)) {
            setPos(newPos);
            updateSprite("right");
        }
    }

    newPos = pos();

    if (activeKeys.contains(Qt::Key_Up) || activeKeys.contains(Qt::Key_Z)) {
        newPos.setY(newPos.y() - 4);
        if (y() > 0 && !checkCollision(newPos)) {
            setPos(newPos);
            updateSprite("back");
        }
    }

    newPos = pos();

    if (activeKeys.contains(Qt::Key_Down) || activeKeys.contains(Qt::Key_S)) {
        newPos.setY(newPos.y() + 4);
        if (y() + pixmap().height() < scene()->height() && !checkCollision(newPos)) {
            setPos(newPos);
            updateSprite("front");
        }
    }
}

void Player::updateSprite(const QString &direction) {
    static const QMap<QString, QStringList> spriteDirections {
        {"left", {":/sprites/player_sprites/leftStandPlayer.png", ":/sprites/player_sprites/leftWalkPlayer1.png", ":/sprites/player_sprites/leftWalkPlayer2.png"}},
        {"right", {":/sprites/player_sprites/rightStandPlayer.png", ":/sprites/player_sprites/rightWalkPlayer1.png", ":/sprites/player_sprites/rightWalkPlayer2.png"}},
        {"back", {":/sprites/player_sprites/backStandPlayer.png", ":/sprites/player_sprites/backWalkPlayer1.png", ":/sprites/player_sprites/backWalkPlayer2.png"}},
        {"front", {":/sprites/player_sprites/frontStandPlayer.png", ":/sprites/player_sprites/frontWalkPlayer1.png", ":/sprites/player_sprites/frontWalkPlayer2.png"}}
    };

    const QStringList &sprites = spriteDirections[direction];
    int step = qRound(direction == "left" || direction == "right" ? x() : y()) % 48;
    int index = step < 16 ? 0 : step < 32 ? 1 : 2;

    setPixmap(QPixmap(sprites[index]).scaled(QSize(11, 16) * scale));
}

void Player::incrementWinCount() {
    winCount++;
}

float Player::getItsLevel() const {
    return itsLevel;
}

void Player::setItsLevel(float newItsLevel) {
    itsLevel = newItsLevel;
}

int Player::getWinCount() const {
    return winCount;
}

void Player::setWinCount(int newWinCount) {
    winCount = newWinCount;
}
