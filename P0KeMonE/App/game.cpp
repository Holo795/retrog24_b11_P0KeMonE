#include "game.h"
#include "player.h"
#include "battle.h"

Game::Game(Model *model, GUI *gui, QWidget *parent)
    : QGraphicsView(parent), model(model), gui(gui) {
    // Configure the initial scene and scaling
    setScene(gui->mainMenu());
    scale(0.55, 0.55); // Scale down for the initial menu view
    setFixedSize(480, 320); // Set fixed size to maintain consistent UI

    // Disable scrollbars for a cleaner look
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Improve rendering quality
    setRenderHint(QPainter::Antialiasing);

    // Setup connections for player encounters and button clicks
    connect(gui->map()->getPlayer(), &Player::startEncounterCombat, this, &Game::showFight);
    connect(gui->battle()->getAttackButton(), &QPushButton::clicked, this, &Game::fight);

    // Initialize timer for fight sequences
    waitFight = new QTimer(this);
    connect(waitFight, &QTimer::timeout, this, &Game::continuefight);

    // Timer for updating the view regularly
    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Game::updateView);
    updateTimer->start(1);
}

Game::~Game() {
    // Deallocate memory for the game model and GUI
    delete model;
    delete gui;

    // Deallocate memory for the player object
    delete player;

    // Deallocate memory for the battle object
    delete battle;

    // Deallocate memory for the waitFight timer
    delete waitFight;
}

void Game::keyPressEvent(QKeyEvent *event) {
    // Handle key presses for game interactions
    if (scene()->focusItem() != nullptr) {

        if (event->key() == Qt::Key_Space)
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
    // Prevent loss of focus when clicking within the game view
    if(scene()->objectName() != gui->battle()->objectName()) return;

    QGraphicsView::mousePressEvent(event);

}

void Game::mouseDoubleClickEvent(QMouseEvent *event){
    // Prevent loss of focus when clicking within the game view
}

void Game::updateView() {
    // Periodically refresh the game scene and re-center if necessary
    scene()->update();
    if(scene()->objectName() == gui->map()->objectName()) {
        centerOn(gui->map()->getPlayer());
    }
}

void Game::showFight() {
    // Switch the scene to the battle interface
    resetTransform();
    setScene(gui->battle(player->getTeam().front(), model->getData()->randompokemon()));
}

void Game::fight() {
    // Manage initiating and processing a battle round

    if(waitFight->isActive()) return;

    battle = new Battle(player, gui->battle()->getPokemon2(), gui->battle());
    battle->attack(&player->getTeam().front()->getItsMoves()[0], gui->battle()->getPokemon2());


    waitFight->start(1000);
}

void Game::continuefight()
{
    // Continue the fight based on battle outcome or player actions

    waitFight->stop();

    battle->attack(&gui->battle()->getPokemon2()->getItsMoves()[0], player->getTeam().front());

    if(gui->battle()->getPokemon1()->getHealth() <= 0)
    {
        resetTransform();
        setScene(gui->gameOver());
        return;
    }
    else if(gui->battle()->getPokemon2()->getHealth() <= 0)
    {
        setScene(gui->map());
        scale(1.5, 1.5);
        return;
    }

}

