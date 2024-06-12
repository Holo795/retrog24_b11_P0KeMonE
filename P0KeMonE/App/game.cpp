#include "game.h"
#include "QtWidgets/qmessagebox.h"
#include "player.h"
#include "maphud.h"
#include <QFontDatabase>
#include <QGraphicsTextItem>

Game::Game(Model *model, GUI *gui, QWidget *parent)
    : QGraphicsView(parent), model(model), gui(gui) {

    setWindowTitle("P0KeMonE");

    QString fontFamily;
    int fontId = QFontDatabase::addApplicationFont(":/hud/battlehud_assets/Minecraft.ttf");
    if (fontId == -1) {
        fontFamily = "Arial";
    } else {
        fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }
    QFont customFont(fontFamily, 9);
    oldMenItem = new QGraphicsPixmapItem(QPixmap(":/map/map_assets/old_men.png"));
    ballsItem = new QGraphicsPixmapItem(QPixmap(":/map/map_assets/ball_open.png"));
    boxItem = new QGraphicsPixmapItem(QPixmap(":/hud/battlehud_assets/dialogue_box.png").scaled(280, 60));
    textItem = new QGraphicsTextItem("", boxItem); // Ajouté en tant qu'enfant de l'élément graphique
    textItem->setPos(QPointF(8, 4)); // Positionner le texte à l'intérieur de l'élément graphique
    textItem->setDefaultTextColor(Qt::black); // Définir la couleur du texte
    textItem->setFont(customFont); // Définir la police et la taille du texte
    textItem->setTextWidth(256); // Définir la largeur du texte pour le retour à la ligne

    // Configure the initial scene and scaling
    currentDialogueIndex = 0;
    setScene(gui->mainMenu());
    setFixedSize(960, 640); // Set fixed size to maintain consistent UI
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
            setBossTeam({model->getData()->pokemonById(244), model->getData()->pokemonById(245), model->getData()->pokemonById(243)});
        }
    }
    if (event->key() == Qt::Key_Space && scene()->objectName() == gui->map()->objectName() && currentDialogueIndex < dialogues.size())
    {
        showNextDialogue();
    }

    if (event->key() == Qt::Key_I && scene()->objectName() == gui->map()->objectName())
        setScene(gui->playerTeam(player->getTeam(), player->getItsLevel()));
    else if(event->key() == Qt::Key_I && scene()->objectName() == gui->team()->objectName())
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

    if (firstFightDone)
    {
        qDebug() << "show first scenario done";
        secondScenarioDone = true;
        gui->map()->removeItem(boxItem);
    }
}

void Game::showNextDialogue() {
    if (currentDialogueIndex < 12 && !firstScenarioDone) {
        textItem->setPlainText(dialogues[currentDialogueIndex]);
        currentDialogueIndex++;
    }
    if (currentDialogueIndex == 12)
    {
        showOldMenChoice();
        currentDialogueIndex++;
    } else
    if (currentDialogueIndex < dialogues.size() && !secondScenarioDone) {
        textItem->setPlainText(dialogues[currentDialogueIndex]);
        currentDialogueIndex++;
    }
}


void Game::showOldMenChoice() {
    setScene(gui->selectPokemon(model->getFirstTeam()));
    qDebug() << "Old Man is speaking";
}

void Game::showFight() {
    // Switch the scene to the battle interface
    firstFightDone = true;
    qDebug() << firstFightDone;
    setScene(gui->battle(player->getTeam().front(), model->getData()->randompokemon()));
    QString menuTextText = QString::fromStdString("Let's go " +gui->battle()->getPokemon1()->getItsName() + " !");
    gui->battle()->getMenuText()->setPlainText(menuTextText);
}

void Game::showBossFight() {
    QGraphicsPixmapItem* bossItem = new QGraphicsPixmapItem(QPixmap(":/hud/battlehud_assets/boss_image.png"));
    bossItem->setPos(QPointF(200, 5)); // Set position separately after creation
    bossItem->setVisible(true);

    // Switch the scene to the boss battle interface
    gui->battle()->addPersonalItem(bossItem);

    setScene(gui->battle(player->getTeam().front(), getBossTeam().front()));

    gui->battle()->getRunButton()->setEnabled(false);
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

void Game::continuefight(bool isBossFight)
{
    showFightMenu();

    // Continue the fight based on battle outcome or player actions
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
        if (isBossFight){
            if(itsBossTeam.size() != 0)
            {
                changePokemon(itsBossTeam.front());
            }
        }
        endFight(true);
    }
    return;
}

void Game::run()
{
    endFight(true);
}

void Game::endFight(bool playerWon)
{
    if (!playerWon) { setScene(gui->gameOver()); return; }

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

void Game::switchPokemon(){
    setScene(gui->selectPokemon(player->getTeam()));
}

void Game::changePokemon(Pokemon* pokemon){
    if(player->getCompleteTeam()) {
        player->setCompleteTeam(false);
        player->addPokemon(pokemon);
        setScene(gui->map());
    } else {
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

