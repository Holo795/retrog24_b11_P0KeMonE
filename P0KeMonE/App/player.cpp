/**
 * @file Player.cpp
 * @brief Implementation of the Player class, which handles player actions and interactions within the game.
 */

#include "player.h"

/**
 * @brief Constructs a Player object with an optional parent item.
 * @param parent The parent QGraphicsItem, default is nullptr.
 */
Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    setZValue(3);
    setPixmap(QPixmap(":/sprites/player_sprites/rightStandPlayer.png").scaled(QSize(11, 16) * scale));

    setTransformationMode(Qt::SmoothTransformation);

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Player::move);
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
 * @brief Initiates movement.
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

/**
 * @brief Adds a Pokémon to the player's team.
 * @param pokemon Pointer to the Pokémon to add.
 */
void Player::addPokemon(Pokemon *pokemon) {
    itsTeam.push_back(pokemon);
}


/**
 * @brief Checks for collisions at the new position.
 * @param newPos The new position to check for collisions.
 * @return true if there is a collision, false otherwise.
 */
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

    setPixmap(QPixmap(sprites[index]).scaled(QSize(11, 16) * scale));
}


void Player::incrementWinCount()
{
    winCount++;
}


/**
 * @brief Returns the current level of this Player.
 */
float Player::getItsLevel() const
{
    return itsLevel;
}

/**
 * @brief Sets the current level of this Player.
 * @param newItsLevel The new level to set.
 */
void Player::setItsLevel(float newItsLevel)
{
    itsLevel = newItsLevel;
}


/**
 * @brief Returns the number of battles won by the player.
 */
int Player::getWinCount() const
{
    return winCount;
}

/**
 * @brief Sets the number of battles won by the player.
 * @param newWinCount The new number of battles won.
 */
void Player::setWinCount(int newWinCount)
{
    winCount = newWinCount;
}

