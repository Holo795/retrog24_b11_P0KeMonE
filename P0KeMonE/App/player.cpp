#include "player.h"

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    setZValue(3);
    setPixmap(QPixmap(":/sprites/player_sprites/backStandPlayer.png").scaled(QSize(11, 16) * scale));
    setTransformationMode(Qt::SmoothTransformation);

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Player::move);

    qDebug() << "Player initialized.";

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

void Player::removePokemon(Pokemon *pokemon)
{
    // Find the Pokémon in the team
    auto it = std::find(itsTeam.begin(), itsTeam.end(), pokemon);

    // If the Pokémon is found, remove it
    if (it != itsTeam.end()) {
        itsTeam.erase(it);
    }

    
}


/**
 * @brief Checks for collisions at the new position.
 * @param newPos The new position to check for collisions.
 * @return true if there is a collision, false otherwise.
 */
bool Player::checkCollision(QPointF newPos) {
    QRectF footPlayerRect(newPos.x() + 2, newPos.y() + pixmap().height() - 2, pixmap().width() - 4, 2);
    QRectF headPlayerRect(newPos.x() + 2, newPos.y(), pixmap().width() - 4, 2);
    QRectF actualFootPlayerRect(pos().x() + 2, pos().y() + pixmap().height() - 2, pixmap().width() - 4, 2);
    QList<QGraphicsItem*> items = scene()->items(QRectF(newPos, QSizeF(pixmap().width(), pixmap().height())));

    for (QGraphicsItem* item : items) {
        if (item == this || item->zValue() + 1 < zValue()) {
            continue;
        }

        int tileId = item->data(0).toInt();
        if (!masks.contains(tileId)) {
            continue;
        }

        const QBitmap& itemMask = masks[tileId];
        QPointF itemTopLeft = item->pos();
        QRectF itemRect(itemTopLeft, itemMask.size());

        QRect baseLayer;
        bool updateZValue = false;

        switch (tileId) {
        case 64: // Lampadaire
            baseLayer = QRect(itemTopLeft.x() + 4, itemTopLeft.y() + 33, 13, 33);
            updateZValue = true;
            break;
        case 65: // Autre lampadaire
            baseLayer = QRect(itemTopLeft.x() + 15, itemTopLeft.y() + 34, 13, 34);
            updateZValue = true;
            break;
        case 93: // Arbre
            baseLayer = QRect(itemTopLeft.x() + 6, itemTopLeft.y() + 25, 58, 41);
            updateZValue = true;
            break;
        case 92: // Pont
        {
            QRect bridge(330, 21 * 32, 640, 65);
            QRect exitBridge(330 + 43, 21 * 32 + 60, 44, 70);

            if ((footPlayerRect.intersects(bridge) && actualFootPlayerRect.intersects(bridge)) ||
                (footPlayerRect.intersects(exitBridge) && actualFootPlayerRect.intersects(exitBridge))) {
                return false;
            }
            break;
        }
        case 83:

            //QRect montain()
            return false;

            break;
        default:
            break;
        }

        if (updateZValue) {
            item->setZValue(headPlayerRect.intersects(itemRect) && !footPlayerRect.intersects(itemRect) ? 2 : 4);
            if (footPlayerRect.intersects(baseLayer)) {
                return true;
            }
            continue;
        }

        // Convertir le rectangle de collision du joueur dans le système de coordonnées de l'item
        QRectF intersectRect = footPlayerRect.intersected(itemRect);
        if (!intersectRect.isEmpty()) {
            QRect playerRectInItemCoords = intersectRect.translated(-itemTopLeft).toRect();
            QImage maskImage = itemMask.toImage();
            for (int y = 0; y < playerRectInItemCoords.height(); ++y) {
                for (int x = 0; x < playerRectInItemCoords.width(); ++x) {
                    if (maskImage.pixelColor(playerRectInItemCoords.topLeft() + QPoint(x, y)) != Qt::transparent) {
                        return true;
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

void Player::setTeam(vector<Pokemon*> newTeam) {
    itsTeam = newTeam;
}
