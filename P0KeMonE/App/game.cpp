#include "game.h"
#include "QtWidgets/qmessagebox.h"
#include "player.h"
#include "maphud.h"
#include <QFontDatabase>
#include <QGraphicsTextItem>

Game::Game(Model *model, GUI *gui, QWidget *parent)
    : QGraphicsView(parent), model(model), gui(gui) {

    setWindowTitle("P0KeMonE");
    setFixedSize(960, 640); // Set fixed size to maintain consistent UI

    QFontDatabase::addApplicationFont(":/hud/battlehud_assets/Minecraft.ttf");

    oldMenItem = new QGraphicsPixmapItem(QPixmap(":/map/map_assets/old_men.png"));
    ballsItem = new QGraphicsPixmapItem(QPixmap(":/map/map_assets/ball_open.png"));
    boxItem = new QGraphicsPixmapItem(QPixmap(":/hud/battlehud_assets/dialogue_box.png").scaled(280, 60));
    textItem = new QGraphicsTextItem("", boxItem); // Ajouté en tant qu'enfant de l'élément graphique
    textItem->setPos(QPointF(8, 4)); // Positionner le texte à l'intérieur de l'élément graphique
    textItem->setDefaultTextColor(Qt::black); // Définir la couleur du texte
    textItem->setFont(QFont("Minecraft", 9)); // Définir la police et la taille du texte
    textItem->setTextWidth(256); // Définir la largeur du texte pour le retour à la ligne

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
    }

    scale(2, 2);

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
            player->setCanMove(false);
            showFirstScenario();
            qDebug() << "First scenario";
            // Définir l'équipe de boss
            setBossTeam({model->getData()->pokemonById(1), model->getData()->pokemonById(7), model->getData()->pokemonById(4)});
        }
    }
    if (event->key() == Qt::Key_Space && scene()->objectName() == gui->map()->objectName() && currentDialogueIndex < dialogues.size() + 1)
    {
        showNextDialogue();
    }

    if (event->key() == Qt::Key_I && scene()->objectName() == gui->map()->objectName() && !player->getTeam().empty())
        setScene(gui->playerTeam(player->getTeam(), player->getItsLevel()));
    else if(event->key() == Qt::Key_I && scene()->objectName() == gui->team()->objectName() && !player->getTeam().empty())
    {
        setScene(gui->map());
    }

    if (event->key() == Qt::Key_Space && scene()->objectName() == gui->gameOver()->objectName())
    {
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

void Game::showFirstScenario() {

    oldMenItem->setPos(1040, 580);

    ballsItem->setPos(1016, 560);

    // Création de l'élément graphique pixmap
    boxItem->setPos(906, 670);

    // Définir Z-value pour mettre l'élément au premier plan
    oldMenItem->setZValue(10);
    ballsItem->setZValue(10);
    boxItem->setZValue(10);

    // Ajouter l'élément graphique à la scène
    gui->map()->addItem(oldMenItem);
    gui->map()->addItem(ballsItem);
    gui->map()->addItem(boxItem);

    if (currentDialogueIndex >= 12)
    {
    gui->map()->removeItem(oldMenItem);
    gui->map()->removeItem(ballsItem);
    gui->map()->removeItem(boxItem);

    qDebug() << "show first scenario done";
    firstScenarioDone = true;
    }
}

void Game::showSecondScenario() {

    player->setPos(910, 820);
    oldMenItem->setPos(910, 760);

    // Création de l'élément graphique pixmap
    boxItem->setPos(776, 860);

    // Définir Z-value pour mettre l'élément au premier plan
    oldMenItem->setZValue(10);
    boxItem->setZValue(10);

    // Ajouter l'élément graphique à la scène
    gui->map()->addItem(oldMenItem);
    gui->map()->addItem(boxItem);
}

void Game::showNextDialogue() {
    if (currentDialogueIndex == 11)
    {
        textItem->setPlainText(dialogues[currentDialogueIndex]);
        showOldMenChoice();
    }
    if (currentDialogueIndex == 12)
    {
        textItem->setPlainText(dialogues[currentDialogueIndex]);
        showFirstFight();
        currentDialogueIndex++;
    }else
    if (currentDialogueIndex < dialogues.size()) {
        textItem->setPlainText(dialogues[currentDialogueIndex]);
        currentDialogueIndex++;
    }else
    {
        player->setCanMove(true);
        gui->battle()->getOldMenPixmap()->setVisible(false);

        gui->map()->removeItem(boxItem);
        gui->map()->removeItem(oldMenItem);
        gui->map()->removeItem(ballsItem);
        player->setPos(1040, 630);
    }
}


void Game::showOldMenChoice() {
    setScene(gui->selectPokemon(model->getFirstTeam()));
}

void Game::showFirstFight() {
    setItsFirstFight(true);
    qDebug() << "First fight";
    gui->battle()->getOldMenPixmap()->setVisible(true);
    Pokemon *firstOpponent = new Pokemon(4, "Old Men' Charmander", Fire, 18, 50, 30, 30, 30, 30, 1);
    firstOpponent->setItsMoves(model->getData()->getMoves(4));
    setScene(gui->battle(player->getTeam().front(),firstOpponent));
    QString menuTextText = QString::fromStdString("Let's go " +gui->battle()->getPokemon1()->getItsName() + " !");
    gui->battle()->getMenuText()->setPlainText(menuTextText);
}

void Game::showBossFight() {
    setItsBossFight(true);
    qDebug() << "Boss fight";
    gui->battle()->getBossPixmap()->setVisible(true);

    setScene(gui->battle(player->getTeam().front(), getBossTeam().front()));
    QString menuTextText = QString::fromStdString("Let's go " +gui->battle()->getPokemon1()->getItsName() + " !");
    gui->battle()->getMenuText()->setPlainText(menuTextText);

    gui->battle()->getRunButton()->setEnabled(false);
}


void Game::showFight() {
    setScene(gui->battle(player->getTeam().front(), model->getData()->randompokemon()));
    QString menuTextText = QString::fromStdString("Let's go " +gui->battle()->getPokemon1()->getItsName() + " !");
    gui->battle()->getMenuText()->setPlainText(menuTextText);
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


    QTimer::singleShot(2000, this, &Game::continuefight);
}

void Game::continuefight()
{

    showFightMenu();

    if(gui->battle()->getPokemon2()->getHealth() <= 0)
    {
        if (getItsBossFight()){
            itsBossTeam.erase(itsBossTeam.begin());
            gui->battle()->getAttackButton()->setEnabled(true);
            gui->battle()->getPokemonButton()->setEnabled(true);
            if(!itsBossTeam.empty())
            {
                setScene(gui->battle(gui->battle()->getPokemon1(), getBossTeam().front()));
            } else {
                endFight(true);
                return;
            }
        } else {
            endFight(true);
            return;
        }
    } else {
        battle->attack(gui->battle()->getPokemon2()->getItsMoves()[0], player->getTeam().front());
    }

    QTimer::singleShot(2000, this, [&](){
        gui->battle()->getAttackButton()->setEnabled(true);
        if(!getItsBossFight()) gui->battle()->getRunButton()->setEnabled(true);
        gui->battle()->getPokemonButton()->setEnabled(true);

        if(gui->battle()->getPokemon1()->getHealth() <= 0)
        {
            player->removePokemon(player->getTeam().front());
            if(!player->getTeam().empty())
            {
                changePokemon(player->getTeam().front());
            }
        }
    });

    return;
}

void Game::run()
{
    endFight(true);
}

void Game::endFight(bool playerWon)
{

    gui->battle()->getAttackButton()->setEnabled(true);
    gui->battle()->getPokemonButton()->setEnabled(true);
    gui->battle()->getRunButton()->setEnabled(true);
    if (!playerWon) {
        qDebug() << "Game Over";
        setScene(gui->gameOver());
        return; }

    if(getItsBossFight() && playerWon) {
        qDebug() << "Boss defeated!";
        setScene(gui->mainMenu()); return;
    }
    if(getItsFirstFight() && playerWon) {
        qDebug() << "First fight done!";
    }

    generateNewOpponent();
    player->incrementWinCount();

    double playerLevel = player->getItsLevel();
    int winsRequired = (playerLevel == 1.0) ? 2 : (playerLevel == 2.0) ? 3 : 5;

    if (player->getWinCount() < winsRequired) { setScene(gui->map()); return; }

    player->setItsLevel(playerLevel + 1.0);
    player->setWinCount(0);

    std::vector<Pokemon*> newPokemons(3);
    std::generate(newPokemons.begin(), newPokemons.end(), [&]() { return model->getData()->randompokemon(); });


    if (player->getTeam().size() < 3)
    {
        player->setCompleteTeam(true);
        setScene(gui->selectPokemon(newPokemons));
    }
    else
    {
        QGraphicsTextItem *pokemonLabel = new QGraphicsTextItem("Veuillez sélectionner un Pokémon à ajouter");
        pokemonLabel->setDefaultTextColor(Qt::black);
        pokemonLabel->setFont(QFont(":/hud/battlehud_assets/Minecraft.ttf", 17, QFont::Bold));
        gui->team()->addItem(pokemonLabel);
        pokemonLabel->setPos(90, 10);
        gui->team()->setPokemons(newPokemons, player->getItsLevel());
        gui->team()->setSelectionMode(true);
        setScene(gui->team());


        QObject::connect(gui->team(), &PlayerHUD::pokemonSelected, this, [=](Pokemon* newPokemon) {
            selectedNewPokemon = newPokemon;
            QObject::disconnect(gui->team(), &PlayerHUD::pokemonSelected, this, nullptr);

            pokemonLabel->setPlainText("Veuillez sélectionner un Pokémon à retirer");

            gui->team()->setPokemons(player->getTeam(), player->getItsLevel());
            gui->team()->setSelectionMode(true);
            setScene(gui->team());

            QObject::connect(gui->team(), &PlayerHUD::pokemonSelected, this, [=](Pokemon* oldPokemon) {
                QObject::disconnect(gui->team(), &PlayerHUD::pokemonSelected, this, nullptr);
                player->removePokemon(oldPokemon);
                player->addPokemon(selectedNewPokemon);
                setScene(gui->map());
                gui->team()->removeItem(pokemonLabel);
            });
        });
    }

    qDebug() << "Level player: " << player->getItsLevel();
    qDebug() << "Wins player: " << player->getWinCount();
}

void Game::generateNewOpponent()
{
    Pokemon* newOpponent = model->getData()->randompokemon();
    gui->battle()->setPokemon(player->getTeam().front(), newOpponent);
}


void Game::setItsBossFight(bool isBossFight)
{
    itsBossFight = isBossFight;
}

bool Game::getItsBossFight()
{
    return itsBossFight;
}

void Game::setItsFirstFight(bool isFirstFight)
{
    itsFirstFight = isFirstFight;
}

bool Game::getItsFirstFight()
{
    return itsFirstFight;
}


void Game::switchPokemon(){
    setScene(gui->selectPokemon(player->getTeam()));
}

void Game::changePokemon(Pokemon* pokemon){
    if(player->getTeam().empty())
    {
        player->addPokemon(pokemon);
        qDebug() << pokemon->getItsName();
        setScene(gui->map());
        showSecondScenario();
    }else if (player->getCompleteTeam()){
        player->setCompleteTeam(false);
        player->addPokemon(pokemon);
        qDebug() << pokemon->getItsName();
        setScene(gui->map());
    }
    else {
        setScene(gui->battle(pokemon, gui->battle()->getPokemon2()));
    }
}

/**
 * @brief Sets the boss's team of Pokémon.
 * @param team Vector of pointers to Pokémon representing the boss's team.
 */
void Game::setBossTeam(std::vector<Pokemon*> team) {
    itsBossTeam = team;
}

/**
 * @brief Retrieves the boss's team of Pokémon.
 * @return A constant reference to a vector of pointers to Pokémon.
 */
std::vector<Pokemon*> Game::getBossTeam() const {
    return itsBossTeam;
}
