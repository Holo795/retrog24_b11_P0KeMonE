#include "game.h"
#include "player.h"
#include "maphud.h"

Game::Game(Model *model, GUI *gui, QWidget *parent)
    : QGraphicsView(parent), model(model), gui(gui) {

    setWindowTitle("P0KeMonE");
    setFixedSize(960, 640); // Set fixed size to maintain consistent UI

    QFontDatabase::addApplicationFont(":/hud/battlehud_assets/Minecraft.ttf");

    // Configure the initial scene and scaling
    setWindowIcon(QIcon(":/hud/battlehud_assets/logoP0KeMonE.png"));

    // Disable scrollbars for a cleaner look
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Improve rendering quality
    setRenderHint(QPainter::Antialiasing);

    // Setup connections for player encounters and button clicks
    connect(gui->map()->getPlayer(), &Player::startEncounterCombat, this, &Game::showFight);
    connect(gui->map()->getPlayer(), &::Player::startEncouterBoss, this, &Game::showBossFight);
    connect(gui->battle()->getAttackButton(), &QPushButton::clicked, this, &Game::showMoves);
    connect(gui->battle()->getPokemonButton(), &QPushButton::clicked, this, &Game::switchPokemon);

    connect(gui->battle()->getMoveGroup(), &QButtonGroup::buttonClicked, this, &Game::onMoveButtonClicked);
    connect(gui->battle()->getBackButton(), &QPushButton::clicked, this, &Game::showFightMenu);

    connect(gui->battle()->getRunButton(), &QPushButton::clicked, this, &Game::run);
    connect(gui->team(), &PlayerHUD::pokemonSelected, this, &Game::changePokemon);

    soundManager = new SoundManager(this);

    // Charger et jouer la musique de fond
    soundManager->loadSound("background", QUrl("qrc:/sounds/sounds/mainMusic.wav"));
    soundManager->playSound("background", true);

    soundManager->loadSound("gameOver", QUrl("qrc:/sounds/sounds/gameOver.wav"));
    soundManager->loadSound("button", QUrl("qrc:/sounds/sounds/button.wav"));

    qDebug() << "Game initialized.";

    setScene(gui->mainMenu());

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
        scale(1.25, 1.25); // Scale up for the battle view
        player->setFocus(); // Set focus on the player object
    } else if (gui->battle()->objectName() == scene->objectName()) {
        itsInFight = true;
        gui->battle()->setText("Let's go " +gui->battle()->getPokemon1()->getItsName() + " !");
    }

    scale(2, 2);

    QGraphicsView::setScene(scene);
}

void Game::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    QString currentScene = scene()->objectName();

    if (key == Qt::Key_Space) {
        soundManager->stopAllSounds();
        handleSpaceKeyPress(currentScene);
    } else if (key == Qt::Key_I || key == Qt::Key_Escape) {
        handleEscIKeyPress(currentScene);
    }

    QGraphicsView::keyPressEvent(event);
}

void Game::handleSpaceKeyPress(QString currentScene) {
    if (currentScene == gui->mainMenu()->objectName()) {
        handleMainMenuSpaceKeyPress();
    } else if (currentScene == gui->map()->objectName() && currentDialogueIndex < dialogues.size() + 1) {
        showNextDialogue();
    } else if (currentScene == gui->gameOver()->objectName()) {
        restartGame();
    }
}

void Game::handleMainMenuSpaceKeyPress() {
    player = gui->map()->getPlayer();
    setScene(gui->map());
    if (player->getTeam().empty()) {
        gui->map()->showFirstScenario();
        itsBossTeam = {
            model->getData()->pokemonById(1),
            model->getData()->pokemonById(7),
            model->getData()->pokemonById(4)
        };
        showNextDialogue();
    }
}

void Game::handleEscIKeyPress(QString currentScene) {
    if (currentScene == gui->map()->objectName() && !player->getTeam().empty()) {
        setScene(gui->playerTeam(player->getTeam(), player->getItsLevel()));
    } else if (currentScene == gui->team()->objectName() && !player->getTeam().empty() && !itsInFight) {
        setScene(gui->map());
    }
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

void Game::restartGame() {
    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();

    QProcess::startDetached(program, arguments);
    QCoreApplication::quit();
}

void Game::showNextDialogue() {

    if(!gui->battle()->getOldMenPixmap()->isVisible())
        return;

    if (currentDialogueIndex == 11)
    {
        gui->map()->getDialogTextItem()->setPlainText(dialogues[currentDialogueIndex]);
        setScene(gui->selectPokemon(model->getPokemonsChoice()));

    }
    if (currentDialogueIndex == 12)
    {
        gui->map()->getDialogTextItem()->setPlainText(dialogues[currentDialogueIndex]);
        showFirstFight();
        currentDialogueIndex++;
    }else if (currentDialogueIndex < dialogues.size())
    {
        gui->map()->getDialogTextItem()->setPlainText(dialogues[currentDialogueIndex]);
        currentDialogueIndex++;
    }else
    {
        gui->battle()->getOldMenPixmap()->setVisible(false);
        gui->map()->endScenario();

    }
}

void Game::showFirstFight() {
    itsFirstFight = true;

    gui->battle()->getOldMenPixmap()->setVisible(true);
    Pokemon *firstOpponent = new Pokemon(4, "Old Men's Charmander", Fire, 18, 50, 30, 30, 30, 30, 1);
    firstOpponent->setItsMoves(model->getData()->getMoves(4));

    setScene(gui->battle(player->getTeam().front(),firstOpponent));
    gui->battle()->getRunButton()->setEnabled(false);
}

void Game::showBossFight() {
    itsBossFight = true;

    gui->battle()->getBossPixmap()->setVisible(true);

    setScene(gui->battle(player->getTeam().front(), itsBossTeam.front()));
    gui->battle()->getRunButton()->setEnabled(false);
}


void Game::showFight() {

    Pokemon* newOpponent = model->getData()->randompokemon();

    if(player->getItsLevel() > 3.0) {
        for(int i = 0; i < player->getItsLevel() - 3; i++) {
            newOpponent->upgradeStats();
        }
        newOpponent->setLevel(player->getItsLevel() - 2);
    }


    setScene(gui->battle(player->getTeam().front(), newOpponent));
}


void Game::showFightMenu() {
    gui->battle()->menuFight();
}

void Game::showMoves() {
    if(soundManager->isPlaying("button")) {
        soundManager->stopSound("button");
        soundManager->playSound("button", false);
    } else {
        soundManager->playSound("button");
    }
    // Retrieve the moves of the player's current Pokémon
    gui->battle()->displayMoves();
}

void Game::onMoveButtonClicked(QAbstractButton *button) {


    int buttonId = gui->battle()->getMoveGroup()->id(button);
    battle = new Battle(gui->battle()->getPokemon1(), gui->battle()->getPokemon2(), gui->battle());

    gui->battle()->disableBattleButtons(true);

    showFightMenu();

    if(soundManager->isPlaying("button")) {
        soundManager->stopSound("button");
        soundManager->playSound("button", false);
    } else {
        soundManager->playSound("button");
    }

    battle->attack(gui->battle()->getPokemon1()->getItsMoves()[buttonId], gui->battle()->getPokemon2());


    QTimer::singleShot(2000, this, &Game::continuefight);
}

void Game::continuefight()
{

    showFightMenu();

    if(gui->battle()->getPokemon2()->getHealth() <= 0)
    {
        if (itsBossFight){
            itsBossTeam.erase(itsBossTeam.begin());
            gui->battle()->enableBattleButtons();
            if(!itsBossTeam.empty())
            {
                setScene(gui->battle(gui->battle()->getPokemon1(), itsBossTeam.front()));
            } else {
                endFight(true);
                return;
            }
        } else {
            endFight(true);
            return;
        }
    } else {
        battle->attack(gui->battle()->getPokemon2()->getRandMove(), player->getTeam().front());
    }

    QTimer::singleShot(2000, this, [&](){
        gui->battle()->enableBattleButtons(!itsBossFight && !itsFirstFight);
        if(gui->battle()->getPokemon1()->getHealth() <= 0)
        {
            player->removePokemon(player->getTeam().front());
            if(!player->getTeam().empty())
            {
                changePokemon(player->getTeam().front());
            } else {
                endFight(false);
            }
        }
    });
}

void Game::run()
{
    if(soundManager->isPlaying("button")) {
        soundManager->stopSound("button");
        soundManager->playSound("button", false);
    } else {
        soundManager->playSound("button");
    }

    endFight(true);
}

void Game::endFight(bool playerWon)
{
    itsInFight = false;

    gui->battle()->enableBattleButtons(true);
    if (!playerWon) {
        qDebug() << "Game Over";
        setScene(gui->gameOver()); return;
    }

    if(itsBossFight) {
        qDebug() << "Boss defeated!";
        setScene(gui->mainMenu()); return;
    }

    if(itsFirstFight) {
        itsFirstFight = false;
        setScene(gui->map());
        return;
    }

    player->incrementWinCount();

    double playerLevel = player->getItsLevel();
    int winsRequired = (playerLevel == 1.0) ? 2 : (playerLevel == 2.0) ? 3 : 5;

    if (player->getWinCount() < winsRequired) { setScene(gui->map()); return; }

    for(Pokemon *pokemon : player->getTeam()) {
        pokemon->upgradeStats();
        pokemon->setLevel(pokemon->getLvl() + 1);
    }

    player->setItsLevel(playerLevel + 1.0);
    player->setWinCount(0);

    std::vector<Pokemon*> newPokemons = model->getPokemonsChoice();

    if (player->getTeam().size() < 3)
    {
        player->setCompleteTeam(true);
    }
    else
    {
        statepokemonChanged = true;
    }

    setScene(gui->selectPokemon(newPokemons, "Qu'elle pokemon tu veux ajouter ?"));


    qDebug() << "Level player: " << player->getItsLevel();
    qDebug() << "Wins player: " << player->getWinCount();
}


void Game::switchPokemon(){
    if(soundManager->isPlaying("button")) {
        soundManager->stopSound("button");
        soundManager->playSound("button", false);
    } else {
        soundManager->playSound("button");
    }

    setScene(gui->selectPokemon(player->getTeam()));
}

void Game::changePokemon(Pokemon* pokemon){
    if(statepokemonChanged){
        if(gui->team()->getPokemonChanged() == nullptr)
        {
            gui->team()->setPokemonChanged(pokemon);
            setScene(gui->selectPokemon(player->getTeam(), "Qu'elle pokemon tu veux retirer ?"));

        }
        else
        {
            player->removePokemon(pokemon);
            player->addPokemon(gui->team()->getPokemonChanged());
            gui->team()->setPokemonChanged(nullptr);
            statepokemonChanged = false;
            setScene(gui->map());
        }
    } else {

        if(player->getTeam().empty())
        {
            player->addPokemon(pokemon);
            setScene(gui->map());
            gui->map()->showSecondScenario();
        }else
        if(player->getCompleteTeam()) {
            player->setCompleteTeam(false);
            player->addPokemon(pokemon);
            setScene(gui->map());
        }
        else
        {
            setScene(gui->battle(pokemon, gui->battle()->getPokemon2()));
        }
    }

}
