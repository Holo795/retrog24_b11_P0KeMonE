#include "game.h"
#include "player.h"

#include <QPushButton>
Game::Game(Model *model, GUI *gui, QWidget *parent)
    : QGraphicsView(parent), model(model), gui(gui) {

    setScene(gui->mainMenu());
    scale(0.55, 0.55);
    setFixedSize(480, 320);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setRenderHint(QPainter::Antialiasing);



    connect(gui->map()->getPlayer(), &Player::startEncounterCombat, this, &Game::showFight);

    connect(gui->battle()->getAttackButton(), &QPushButton::clicked, this, &Game::fight);

    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Game::updateView);
    updateTimer->start(1);
}

Game::~Game() {}

void Game::keyPressEvent(QKeyEvent *event) {
    if (scene()->focusItem() != nullptr) {

        if (scene()->objectName() == gui->mainMenu()->objectName() && event->key() == Qt::Key_Space)
        {
            resetTransform();
            setScene(gui->map());
            scale(1.5, 1.5);
        }

        QGraphicsView::keyPressEvent(event);
    }
}

void Game::mousePressEvent(QMouseEvent *event){
    if(scene()->objectName() != gui->battle()->objectName()) return;

    QGraphicsView::mousePressEvent(event);

}

void Game::mouseDoubleClickEvent(QMouseEvent *event){}

void Game::updateView() {
    scene()->update();
    if(scene()->objectName() == gui->map()->objectName()) {
        centerOn(gui->map()->getPlayer());
    }
}

void Game::showFight() {
    resetTransform();
    setScene(gui->battle(model->getData()->randompokemon(), model->getData()->randompokemon()));
}

void Game::fight() {
    qDebug() << "azdfgn,";
}

