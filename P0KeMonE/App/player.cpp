#include "player.h"

/**
 * Initializes the Player object, sets up its graphical representation and movement mechanics.
 */
Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    setZValue(2);
    setPixmap(QPixmap(":/player/leftStandPlayer.png").scaled(QSize(11, 16) * scale));  // Assurez-vous de mettre le bon chemin vers l'image du joueur

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Player::move);
}

/**
 * Destructor for the Player class.
 */
Player::~Player() {
    delete movementTimer;
}

/**
 * Checks for potential collisions at a new position.
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
 * Initiates movement based on a key press.
 */
void Player::startMoving(int key) {
    currentKey = key;
    movementTimer->start(30);
}

/**
 * Stops movement when a key is released.
 */
void Player::stopMoving() {
    movementTimer->stop();
    currentKey = 0; // Reset the current key
}

/**
 * Moves the player based on the current key press.
 */
void Player::move() {
    if (!currentKey) return; // Do nothing if no key is pressed

    // Handle movement and animation logic
    QPointF newPos;
    switch (currentKey) {
    case Qt::Key_Left:
        newPos = pos() + QPointF(-4, 0);
        if (newPos.x() > 0 && !checkCollision(newPos)) {
            setPos(newPos);
            if (qRound(x()) % 48 >= 16 && qRound(x()) % 48 < 32) {
                setPixmap(QPixmap(":/player/leftWalkPlayer1.png").scaled(QSize(10, 16) * scale));
            } else if (qRound(x()) % 48 >= 32) {
                setPixmap(QPixmap(":/player/leftWalkPlayer2.png").scaled(QSize(11, 16) * scale));
            } else {
                setPixmap(QPixmap(":/player/leftStandPlayer.png").scaled(QSize(11, 16 )* scale));
            }
        }
        break;
    case Qt::Key_Right:
        newPos = pos() + QPointF(4, 0);
        if (newPos.x() + pixmap().width() < scene()->width() && !checkCollision(newPos)) {
            setPos(newPos);
            if (qRound(x()) % 48 >= 16 && qRound(x()) % 48 < 32) {
                setPixmap(QPixmap(":/player/rightWalkPlayer1.png").scaled(QSize(11, 16) * scale));
            } else if (qRound(x()) % 48 >= 32) {
                setPixmap(QPixmap(":/player/rightWalkPlayer2.png").scaled(QSize(11, 16) * scale));
            } else {
                setPixmap(QPixmap(":/player/rightStandPlayer.png").scaled(QSize(11, 16) * scale));
            }
        }
        break;
    case Qt::Key_Up:
        newPos = pos() + QPointF(0, -4);
        if (newPos.y() > 0 && !checkCollision(newPos)) {
            setPos(newPos);
            if (qRound(y()) % 48 >= 16 && qRound(y()) % 48 < 32) {
                setPixmap(QPixmap(":/player/backWalkPlayer1.png").scaled(QSize(11, 16) * scale));
            } else if (qRound(y()) % 48 >= 32) {
                setPixmap(QPixmap(":/player/backWalkPlayer2.png").scaled(QSize(11, 16) * scale));
            } else {
                setPixmap(QPixmap(":/player/backStandPlayer.png").scaled(QSize(11, 16) * scale));
            }
        }
        break;
    case Qt::Key_Down:
        newPos = pos() + QPointF(0, 4);
        if (newPos.y() + pixmap().height() < scene()->height() && !checkCollision(newPos)) {
            setPos(newPos);
            if (qRound(y()) % 48 >= 16 && qRound(y()) % 48 < 32) {
                setPixmap(QPixmap(":/player/frontWalkPlayer1.png").scaled(QSize(11, 16) * scale));
            } else if (qRound(y()) % 48 >= 32) {
                setPixmap(QPixmap(":/player/frontWalkPlayer2.png").scaled(QSize(11, 16) * scale));
            } else {
                setPixmap(QPixmap(":/player/frontStandPlayer.png").scaled(QSize(11, 16) * scale));
            }
        }
        break;
    }
}

/**
 * Returns the team of Pokémon.
 */
std::vector<Pokemon*> Player::getTeam() const
{
    return itsTeam;
}

/**
 * Handles key press events to initiate movement.
 */
void Player::keyPressEvent(QKeyEvent *event) {
    if (!movementTimer->isActive()) {
        startMoving(event->key()); // Start moving in the direction of the key press
    }
}

/**
 * Handles key release events to stop movement.
 */
void Player::keyReleaseEvent(QKeyEvent *event) {
    stopMoving();
}

/**
 * Adds a Pokémon to the player's team.
 */
void Player::addPokemon(Pokemon *pokemon)
{
    itsTeam.push_back(pokemon); // Add the new Pokémon to the team
}


