#include "game.h"
#include "player.h"
#include "battle.h"

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

    waitFight = new QTimer(this);
    connect(waitFight, &QTimer::timeout, this, &Game::continuefight);

    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Game::updateView);
    updateTimer->start(1);
}

Game::~Game() {}

void Game::drawMap()
{

}

void Game::keyPressEvent(QKeyEvent *event) {
    if (scene()->focusItem() != nullptr) {

        if (scene()->objectName() == gui->mainMenu()->objectName() && event->key() == Qt::Key_Space)
        {
            resetTransform();
            setScene(gui->map());
            scale(1.5, 1.5);
            player = gui->map()->getPlayer();
            if(player->getTeam().empty())
            {
                player->addPokemon(model->getData()->randompokemon());
                qDebug() << player->getTeam().front()->getItsMoves().size();
            }
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
    setScene(gui->battle(player->getTeam().front(), model->getData()->randompokemon()));
}

void Game::fight() {
    if(waitFight->isActive()) return;

    battle = new Battle(player, gui->battle()->getPokemon2(), gui->battle());
    battle->attack(&player->getTeam().front()->getItsMoves()[0], gui->battle()->getPokemon2());


    waitFight->start(1000);
}

void Game::continuefight()
{
    waitFight->stop();

    if(gui->battle()->getPokemon1()->getHealth() <= 0)
    {
        resetTransform();
        setScene(gui->gameOver());

    }

    if(gui->battle()->getPokemon2()->getHealth() <= 0)
    {
        scale(1.5, 1.5);
        setScene(gui->map());

    }
    battle->attack(&gui->battle()->getPokemon2()->getItsMoves()[0], player->getTeam().front());

}

