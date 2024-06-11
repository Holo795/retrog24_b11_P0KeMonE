#include "game.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qmessagebox.h"
#include "player.h"


Game::Game(Model *model, GUI *gui, QWidget *parent)
    : QGraphicsView(parent), model(model), gui(gui) {

    setWindowTitle("P0KeMonE");

    // Configure the initial scene and scaling
    setScene(gui->mainMenu());
    setFixedSize(480, 320); // Set fixed size to maintain consistent UI
    setWindowIcon(QIcon(":/hud/battlehud_assets/logoP0KeMonE.png"));

    // Disable scrollbars for a cleaner look
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Improve rendering quality
    setRenderHint(QPainter::Antialiasing);

    // Setup connections for player encounters and button clicks
    connect(gui->map()->getPlayer(), &Player::startEncounterCombat, this, &Game::showFight);
    connect(gui->map()->getPlayer(), &::Player::startEncouterBoss, this, &Game::showBossFight);
    connect(gui->map()->getPlayer(), &::Player::startEncouterOldMen, this, &Game::showOldMenSpeach);
    connect(gui->battle()->getAttackButton(), &QPushButton::clicked, this, &Game::showMoves);
    connect(gui->battle()->getPokemonButton(), &QPushButton::clicked, this, &Game::switchPokemon);

    connect(gui->battle()->getMoveGroup(), &QButtonGroup::buttonClicked, this, &Game::onMoveButtonClicked);
    connect(gui->battle()->getBackButton(), &QPushButton::clicked, this, &Game::showFightMenu);

    connect(gui->battle()->getRunButton(), &QPushButton::clicked, this, &Game::run);
    connect(gui->team(), &PlayerHUD::pokemonSelected, this, &Game::changePokemon);

    soundManager = new SoundManager(this);

    qDebug() << "Game initialized.";

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

    if (event->key() == Qt::Key_Space && scene()->objectName() == "GameOverHUD") {
        player->setItsLevel(1.0);
        player->setWinCount(0);
        std::vector<Pokemon*> emptyTeam;
        player->setTeam(emptyTeam);
        player->setPos(200, 950);


        setScene(gui->mainMenu());

    }

    QGraphicsView::keyPressEvent(event);

}

void Game::mousePressEvent(QMouseEvent *event){
    // Prevent loss of focus when clicking within the game view
    if(scene()->objectName() != gui->battle()->objectName()) return;

    QGraphicsView::mousePressEvent(event);

}

void Game::mouseDoubleClickEvent(QMouseEvent *){
    // Prevent loss of focus when clicking within the game view
}

void Game::focusOutEvent(QFocusEvent *){
    // Prevent loss of focus when clicking within the game view
}

void Game::focusInEvent(QFocusEvent *){
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
    QString menuTextText = QString::fromStdString("Let's go " +gui->battle()->getPokemon1()->getItsName() + " !");
    gui->battle()->getMenuText()->setPlainText(menuTextText);
}

void Game::showBossFight() {
    // Switch the scene to the boss battle interface
    //setScene(gui->battle(player->getTeam().front(), battle->getBossTeam().front()));
    qDebug() << "boss fight";
}

void Game::showOldMenSpeach() {
    // Afficher un message dans la console pour confirmer l'affichage du dialogue
    setScene(gui->selectPokemon(model->getFirstTeam()));
    qDebug() << "Old Man is speaking";
}


void Game::showFightMenu() {
    gui->battle()->menuFight();
}

void Game::showMoves() {
    // Retrieve the moves of the player's current Pokémon
    gui->battle()->displayMoves();
}

void Game::onMoveButtonClicked(QAbstractButton *button) {


    int buttonId = gui->battle()->getMoveGroup()->id(button);
    battle = new Battle(gui->battle()->getPokemon1(), gui->battle()->getPokemon2(), gui->battle());

    gui->battle()->getAttackButton()->setEnabled(false);
    gui->battle()->getRunButton()->setEnabled(false);
    gui->battle()->getPokemonButton()->setEnabled(false);

    showFightMenu();

    battle->attack(gui->battle()->getPokemon1()->getItsMoves()[buttonId], gui->battle()->getPokemon2());

    QTimer::singleShot(1000, this, &Game::continuefight);
}

void Game::continuefight()
{
    showFightMenu();

    battle->attack(gui->battle()->getPokemon2()->getItsMoves()[0], player->getTeam().front());

    QTimer::singleShot(1000, this, [&](){
        gui->battle()->getAttackButton()->setEnabled(true);
        gui->battle()->getRunButton()->setEnabled(true);
        gui->battle()->getPokemonButton()->setEnabled(true);
    });

    if(gui->battle()->getPokemon1()->getHealth() <= 0)
    {
        player->removePokemon(player->getTeam().front());
        if(player->getTeam().size() != 0)
        {
            changePokemon(player->getTeam().front());
        }
    }
    else if(gui->battle()->getPokemon2()->getHealth() <= 0)
    {
        endFight(true);
    }
    return;
}






void Game::run()
{
    endFight(true);
    //setScene(gui->map());
}

void Game::endFight(bool playerWon)
{
    if (playerWon)
    {
        generateNewOpponent();
        player->incrementWinCount();

        double initialPlayerLevel = player->getItsLevel();
        int winsRequired = 0;

        if (player->getItsLevel() == 1.0) {
            winsRequired = 2;
        } else if (player->getItsLevel() == 2.0) {
            winsRequired = 3;
        } else if (player->getItsLevel() >= 3.0) {
            winsRequired = 5;
        }

        if (player->getWinCount() >= winsRequired)
        {
            player->setItsLevel(player->getItsLevel() + 1.0);


            player->setWinCount(0); // Réinitialise le compteur de victoires après avoir passé le niveau



            if (player->getItsLevel() != initialPlayerLevel) {
                qDebug() << "Le joueur a gagné un niveau !";
                std::vector<Pokemon*> newPokemons;

                for (int i = 0; i < 3; i++) {
                    newPokemons.push_back(model->getData()->randompokemon());
                }

                if(player->getTeam().size() < 3)
                {
                    player->addPokemon(model->getData()->randompokemon());
                    setScene(gui->map());
                }
                else
                {
                    gui->team()->setPokemonLabel(new QGraphicsTextItem("Veuillez sélectionner un Pokémon à échanger"));

                    gui->team()->setPokemons(newPokemons, player->getItsLevel());
                    gui->team()->setSelectionMode(true);
                    setScene(gui->team());



                    qDebug() << "Connect the signal for selecting the new Pokémon";
                    QObject::connect(gui->team(), &PlayerHUD::pokemonSelected, this, [=](Pokemon* newPokemon) {
                        qDebug() << "Nouveau Pokémon sélectionné";
                        selectedNewPokemon = newPokemon;

                        QObject::disconnect(gui->team(), &PlayerHUD::pokemonSelected, this, nullptr);

                        // Afficher l'interface de sélection des Pokémon actuels de l'équipe
                        gui->team()->setPokemonLabel(new QGraphicsTextItem("Veuillez sélectionner un Pokémon à retirer"));
                        gui->team()->setPokemons(player->getTeam(), player->getItsLevel());
                        gui->team()->setSelectionMode(true);
                        setScene(gui->team());


                        // Connecter le signal pour la sélection du Pokémon à retirer
                        qDebug() << "Connect the signal for selecting the Pokémon to remove";
                        QObject::connect(gui->team(), &PlayerHUD::pokemonSelected, this, [=](Pokemon* oldPokemon) {
                            qDebug() << "Ancien Pokémon sélectionné";
                            QObject::disconnect(gui->team(), &PlayerHUD::pokemonSelected, this, nullptr);

                            // Retirer le Pokémon sélectionné et ajouter le nouveau Pokémon
                            player->removePokemon(oldPokemon);
                            player->addPokemon(selectedNewPokemon);

                            // Retourner à la carte après la mise à jour de l'équipe
                            setScene(gui->map());
                        });
                    });
                }

            }
        }
        else
        {
            setScene(gui->map());

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
