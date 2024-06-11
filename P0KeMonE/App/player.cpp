#include "player.h"

/**
 * @brief Constructs a Player object with an optional parent item.
 * @param parent The parent QGraphicsItem, default is nullptr.
 */
Player::Player(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), movementTimer(new QTimer(this))
{
    setZValue(3);
    setPixmap(QPixmap(":/sprites/player_sprites/backStandPlayer.png").scaled(QSize(11, 16) * scale));
    setTransformationMode(Qt::SmoothTransformation);

    connect(movementTimer, &QTimer::timeout, this, &Player::move);

    qDebug() << "Player initialized.";
}

/**
 * @brief Destructor for the Player class.
 */
Player::~Player() {
    delete movementTimer;
}

/**
 * @brief Retrieves the player's team of Pokémon.
 * @return A constant reference to a vector of pointers to Pokémon.
 */
std::vector<Pokemon*> Player::getTeam() const {
    return itsTeam;
}

/**
 * @brief Sets the player's team of Pokémon.
 * @param newTeam A vector of pointers to Pokémon.
 */
void Player::setTeam(const std::vector<Pokemon*>& newTeam) {
    itsTeam = newTeam;
}

/**
 * @brief Adds a Pokémon to the player's team.
 * @param pokemon Pointer to the Pokémon to add.
 */
void Player::addPokemon(Pokemon *pokemon) {
    itsTeam.push_back(pokemon);
}

/**
 * @brief Removes a Pokémon from the player's team.
 * @param pokemon Pointer to the Pokémon to remove.
 */
void Player::removePokemon(Pokemon *pokemon) {
    auto it = std::find(itsTeam.begin(), itsTeam.end(), pokemon);
    if (it != itsTeam.end()) {
        itsTeam.erase(it);
    }
}

/**
 * @brief Handles key press events for player movement.
 * @param event The key event.
 */
void Player::keyPressEvent(QKeyEvent *event) {
    activeKeys.insert(event->key());
    if (!movementTimer->isActive()) {
        startMoving();
    }
}

/**
 * @brief Handles key release events to stop player movement.
 * @param event The key event.
 */
void Player::keyReleaseEvent(QKeyEvent *event) {
    activeKeys.remove(event->key());
    if (activeKeys.isEmpty()) {
        stopMoving();
    }
}

/**
 * @brief Initiates movement in a specific direction.
 */
void Player::startMoving() {
    movementTimer->start(30);
}

/**
 * @brief Stops the player's movement.
 */
void Player::stopMoving() {
    movementTimer->stop();
    activeKeys.clear();
}

void Player::handleKeyPress(QKeyEvent *event) {
    keyPressEvent(event);
}

void Player::handleKeyRelease(QKeyEvent *event) {
    keyReleaseEvent(event);
}


/**
 * @brief Checks for collisions at the new position.
 * @param newPos The new position to check for collisions.
 * @return true if there is a collision, false otherwise.
 */
bool Player::checkCollision(QPointF newPos) const {
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
        case 67:
        case 68:
            return false;
        case 83:
        {
            QRect montain(970, 551, 188, 172 + 10);
            QRect bridge_montain(934, 671, 28, 52 + 10);
            QRect exitMontain(1034, 731, 50, 50);

            qDebug() << footPlayerRect;
            qDebug() << actualFootPlayerRect;

            if (footPlayerRect.intersects(montain) && actualFootPlayerRect.intersects(montain)) {
                return false;
            }

            if (footPlayerRect.intersects(bridge_montain) && actualFootPlayerRect.intersects(bridge_montain)) {
                return false;
            }

            if (footPlayerRect.intersects(exitMontain) && actualFootPlayerRect.intersects(exitMontain)) {
                return false;
            }

            break;
        }
        case 92: // Pont
        {
            QRect bridge(330, 21 * 32, 640, 65);
            QRect exitBridge(330 + 43, 21 * 32 + 60, 44, 70);

            if (footPlayerRect.intersects(bridge) && actualFootPlayerRect.intersects(bridge)) {
                return false;
            }

            if (footPlayerRect.intersects(exitBridge) && actualFootPlayerRect.intersects(exitBridge)) {
                return false;
            }

            break;
        }
        case 93: // Arbre
            baseLayer = QRect(itemTopLeft.x() + 6, itemTopLeft.y() + 25, 58, 43);
            updateZValue = true;
            break;
        case 96:
        {
            baseLayer = QRect(itemTopLeft.x() + 5, itemTopLeft.y() + 21, 20, 16);
            updateZValue = true;
            emit signEncounter(itemRect.x(), itemRect.y());
            break;
        }
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

/**
 * @brief Moves the player based on the currently pressed key.
 */
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

/**
 * @brief Updates the player's sprite based on the direction.
 * @param direction The direction in which the player is moving.
 */
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

    setPixmap(QPixmap(sprites[index]).scaled(QSize(12, 18) * scale));
}

/**
 * @brief Retrieves the player's current level.
 * @return The player's current level.
 */
float Player::getItsLevel() const {
    return itsLevel;
}

/**
 * @brief Sets the player's current level.
 * @param newItsLevel The new level to set.
 */
void Player::setItsLevel(float newItsLevel) {
    itsLevel = newItsLevel;
}

/**
 * @brief Retrieves the player's win count.
 * @return The player's win count.
 */
int Player::getWinCount() const {
    return winCount;
}

/**
 * @brief Sets the player's win count.
 * @param newWinCount The new win count to set.
 */
void Player::setWinCount(int newWinCount) {
    winCount = newWinCount;
}

/**
 * @brief Increments the player's win count.
 */
void Player::incrementWinCount() {
    winCount++;
}
