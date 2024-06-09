#include "game.h"
#include "player.h"
#include "battle.h"


Game::Game(Model *model, GUI *gui, QWidget *parent)
    : QGraphicsView(parent), model(model), gui(gui) {
    // Configure the initial scene and scaling
    setScene(gui->mainMenu());
    setFixedSize(480, 320); // Set fixed size to maintain consistent UI

    // Disable scrollbars for a cleaner look
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Improve rendering quality
    setRenderHint(QPainter::Antialiasing);

    // Setup connections for player encounters and button clicks
    connect(gui->map()->getPlayer(), &Player::startEncounterCombat, this, &Game::showFight);
    connect(gui->battle()->getAttackButton(), &QPushButton::clicked, this, &Game::showMoves);
    connect(gui->battle()->getPokemonButton(), &QPushButton::clicked, this, &Game::switchPokemon);

    connect(gui->battle()->getMoveGroup(), &QButtonGroup::buttonClicked, this, &Game::onMoveButtonClicked);
    connect(gui->battle()->getBackButton(), &QPushButton::clicked, this, &Game::showFightMenu);

    connect(gui->battle()->getRunButton(), &QPushButton::clicked, this, &Game::run);
    connect(gui->team(), &PlayerHUD::pokemonSelected, this, &Game::changePokemon);

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

void Game::setScene(QGraphicsScene *scene) {
    // Set the current scene for the game view
    resetTransform();

    if(player != nullptr)
        player->stopMoving();

    if(gui->mainMenu()->objectName() == scene->objectName()) {
            scale(0.55, 0.55); // Scale down for the initial menu view
    } else if (gui->map()->objectName() == scene->objectName()) {
            scale(1.5, 1.5); // Scale up for the battle view
            player->setFocus(); // Set focus on the player object
    }

    QGraphicsView::setScene(scene);
}

void Game::keyPressEvent(QKeyEvent *event) {
    // Handle key presses for game interactions
    if (event->key() == Qt::Key_Space && scene()->objectName() == gui->mainMenu()->objectName())
    {
        player = gui->map()->getPlayer();
        setScene(gui->map());
        if(player->getTeam().empty())
        {
            player->addPokemon(model->getData()->randompokemon());

            player->addPokemon(model->getData()->randompokemon());
            qDebug() << player->getTeam().front()->getItsMoves().size();
        }
        //battle->getBossTeam()

    };

    if (event->key() == Qt::Key_I && scene()->objectName() == gui->map()->objectName())
        setScene(gui->playerTeam(player->getTeam(), player->getItsLevel()));
    else if(event->key() == Qt::Key_I && scene()->objectName() == gui->team()->objectName()) {
        setScene(gui->map());
    }

    QGraphicsView::keyPressEvent(event);

}

void Game::mousePressEvent(QMouseEvent *event){
    // Prevent loss of focus when clicking within the game view
    if(scene()->objectName() != gui->battle()->objectName()) return;

    QGraphicsView::mousePressEvent(event);

}

void Game::mouseDoubleClickEvent(QMouseEvent *event){
    // Prevent loss of focus when clicking within the game view
}

void Game::focusOutEvent(QFocusEvent *event){
    // Prevent loss of focus when clicking within the game view
}

void Game::focusInEvent(QFocusEvent *event){
    // Prevent loss of focus when clicking within the game view
    if (scene()->objectName() == gui->map()->objectName()) {
        player->setFocus();
    }
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
    setScene(gui->battle(player->getTeam().front(), model->getData()->randompokemon()));
}

void Game::showFightMenu() {
    gui->battle()->menuFight();
}

void Game::showMoves() {
    // Retrieve the moves of the player's current Pokémon
    QList<Move*> movePk1 = gui->battle()->getPokemon1()->getItsMoves();
    gui->battle()->displayMoves(movePk1);
}

void Game::onMoveButtonClicked(QAbstractButton *button) {

    int buttonId = gui->battle()->getMoveGroup()->id(button);
    battle = new Battle(gui->battle()->getPokemon1(), gui->battle()->getPokemon2(), gui->battle());

    for (QAbstractButton *button : gui->battle()->getMoveGroup()->buttons()) {
        button->setEnabled(false);
    }

    battle->attack(gui->battle()->getPokemon1()->getItsMoves()[buttonId], gui->battle()->getPokemon2());

    QTimer::singleShot(2000, this, &Game::continuefight);

}

void Game::continuefight()
{
    // Continue the fight based on battle outcome or player actions

    battle->attack(gui->battle()->getPokemon2()->getItsMoves()[0], gui->battle()->getPokemon1());

    QTimer::singleShot(1000, this, [&](){
        for (QAbstractButton *button : gui->battle()->getMoveGroup()->buttons()) {
            button->setEnabled(true);
        }
    });

    if(gui->battle()->getPokemon1()->getHealth() <= 0){
        endFight(false);
    }else if(gui->battle()->getPokemon2()->getHealth() <= 0){
        endFight(true);
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
        player->incrementWinCount();
        double playerLevel = player->getItsLevel();
        int winsRequired = 0;

        if (playerLevel == 1.0) {
            winsRequired = 1;
        } else if (playerLevel == 2.0) {
            winsRequired = 2;
        } else if (playerLevel >= 3.0) {
            winsRequired = 5;
        }

        if (player->getWinCount() >= winsRequired) {
            player->setItsLevel(playerLevel + (playerLevel >= 3.0 ? 1.0 : 0.5));
            player->setWinCount(0); // Réinitialise le compteur de victoires après avoir passé le niveau
        }


        qDebug() << "Level player: " << player->getItsLevel();
        qDebug() << "Wins player: " << player->getWinCount();
    }
    else
    {
        setScene(gui->gameOver());
    }
}

void Game::generateNewOpponent()
{
    Pokemon* newOpponent = model->getData()->randompokemon();
    gui->battle()->setPokemon(player->getTeam().front(), newOpponent);
}

void Game::switchPokemon(){
    setScene(gui->selectPokemon(player->getTeam()));
}

void Game::changePokemon(Pokemon* pokemon){
    setScene(gui->battle(pokemon, gui->battle()->getPokemon2()));
}
