#include "game.h"
#include "player.h"
#include "battle.h"
#include "qbuttongroup.h"


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
    connect(gui->battle()->getAttackButton(), &QPushButton::clicked, this, &Game::showMoves);

    //connect(gui->battle()->getPokemonButton(), &QPushButton::clicked, this, &Game::switchPokemon);
    connect(gui->battle()->getRunButton(), &QPushButton::clicked, this, &Game::run);


    connect(gui->battle()->getMoveGroup(), &QButtonGroup::buttonClicked,
            this, &Game::handleAttackButtonClicked);

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
    battle = new Battle(player, gui->battle()->getPokemon2(), gui->battle());

    // Assuming the player has already selected a move, for example:
    Move selectedMove = player->getTeam().front()->getItsMoves()[0]; // Change this based on player's choice
    battle->attack(&selectedMove, gui->battle()->getPokemon2());

    QTimer::singleShot(2000, this, &Game::continuefight);

}

void Game::showMoves() {
    // Retrieve the moves of the player's current Pokémon
    QList<Move> movePk1 = player->getTeam().front()->getItsMoves();
    gui->battle()->displayMoves(movePk1);
}

void Game::handleAttackButtonClicked(QAbstractButton *button) {
    // Réagir en fonction de l'indice du bouton cliqué
    int buttonId = gui->battle()->getMoveGroup()->id(button);

    switch (buttonId) {
    case 0:
        qDebug() << "1 bouton d'attaque cliqué";
        break;
    case 1:
        qDebug() << "2 bouton d'attaque cliqué";
        break;
    case 2:
        qDebug() << "3 bouton d'attaque cliqué";
        break;
    case 3:
        qDebug() << "4 bouton d'attaque cliqué";
        break;
    case 4:
        qDebug() << "5 bouton back";
        break;
    default:
        qDebug() << "default";
    }
}

void Game::continuefight()
{
    // Continue the fight based on battle outcome or player actions

    battle->attack(&gui->battle()->getPokemon2()->getItsMoves()[0], player->getTeam().front());

    QTimer::singleShot(1000, this, [&](){
        gui->battle()->getAttackButton()->setEnabled(true);
    });

    if(gui->battle()->getPokemon1()->getHealth() <= 0)
    {
        endFight(false);
        return;
    }
    else if(gui->battle()->getPokemon2()->getHealth() <= 0)
    {
        endFight(true);
        return;
    }

}

void Game::run()
{
    endFight(true);
}

void Game::endFight(bool playerWon)
{
    if (playerWon)
    {
        generateNewOpponent();
        setScene(gui->map());
        scale(1.5, 1.5);
    }
    else
    {
        resetTransform();
        setScene(gui->gameOver());
    }

}

void Game::generateNewOpponent()
{
    Pokemon* newOpponent = model->getData()->randompokemon();
    gui->battle()->setPokemon(player->getTeam().front(), newOpponent);
}
