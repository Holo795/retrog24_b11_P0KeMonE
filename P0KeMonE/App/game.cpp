#include "game.h"
#include "QtWidgets/qmessagebox.h"
#include "player.h"
#include "maphud.h"
#include <QFontDatabase>
#include <QGraphicsTextItem>

/**
 * @brief Constructor for the Game class.
 * @param model Pointer to the game model.
 * @param gui Pointer to the GUI.
 * @param parent Pointer to the parent widget.
 */
Game::Game(Model *model, GUI *gui, QWidget *parent)
    : QGraphicsView(parent), model(model), gui(gui), player(nullptr), battle(nullptr) {

    setWindowTitle("P0KeMonE");

    // Configure the initial scene and scaling
    currentDialogueIndex = 0;
    setScene(gui->mainMenu());
    setFixedSize(960, 640);
    setWindowIcon(QIcon(":/hud/battlehud_assets/logoP0KeMonE.png"));

    // Disable scrollbars for a cleaner look
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Improve rendering quality
    setRenderHint(QPainter::Antialiasing);

    // Setup connections for player encounters and button clicks
    setupConnections();

    soundManager = new SoundManager(this);

    qDebug() << "Game initialized.";

    // Timer for updating the view regularly
    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Game::updateView);
    updateTimer->start(1);
}

/**
 * @brief Destructor for the Game class.
 */
Game::~Game() {
    delete model;
    delete gui;
    delete player;
    delete battle;
}

/**
 * @brief Set the current scene for the game view.
 * @param scene Pointer to the QGraphicsScene.
 */
void Game::setScene(QGraphicsScene *scene) {
    resetTransform();

    if(player != nullptr)
        player->stopMoving();
    if(gui->mainMenu()->objectName() == scene->objectName()) {
        scale(0.55, 0.55);
    } else if (gui->map()->objectName() == scene->objectName()) {
        scale(1.5, 1.5);
        player->setFocus();
    }

    scale(2, 2);

    QGraphicsView::setScene(scene);
}

/**
 * @brief Handle key press events for game interactions.
 * @param event Pointer to the QKeyEvent.
 */
void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && scene()->objectName() == gui->mainMenu()->objectName()) {
        showFirstScenario();
    } else if (event->key() == Qt::Key_Space && scene()->objectName() == gui->map()->objectName() && currentDialogueIndex < dialogues.size()) {
        showNextDialogue();
    } else if (event->key() == Qt::Key_I && scene()->objectName() == gui->map()->objectName()) {
        setScene(gui->playerTeam(player->getTeam(), player->getItsLevel()));
    } else if(event->key() == Qt::Key_I && scene()->objectName() == gui->team()->objectName()) {
        setScene(gui->map());
    } else if (event->key() == Qt::Key_Space && scene()->objectName() == gui->gameOver()->objectName()) {
        resetGame();
    }
    QGraphicsView::keyPressEvent(event);
}

/**
 * @brief Handle mouse press events to prevent loss of focus.
 * @param event Pointer to the QMouseEvent.
 */
void Game::mousePressEvent(QMouseEvent *event) {
    if(scene()->objectName() != gui->battle()->objectName()) return;
    QGraphicsView::mousePressEvent(event);
}

void Game::mouseDoubleClickEvent(QMouseEvent *) {}
void Game::focusOutEvent(QFocusEvent *) {}
void Game::focusInEvent(QFocusEvent *) {
    if (scene()->objectName() == gui->map()->objectName()) {
        player->setFocus();
    }
}

/**
 * @brief Periodically refresh the game scene and re-center if necessary.
 */
void Game::updateView() {
    scene()->update();
    if(scene()->objectName() == gui->map()->objectName()) {
        centerOn(gui->map()->getPlayer());
    }
}

/**
 * @brief Display the first scenario.
 */
void Game::showFirstScenario() {
    oldMenItem = createGraphicsItem(":/map/map_assets/old_men.png", QPointF(1040, 560), QSize(24, 32));
    ballsItem = createGraphicsItem(":/map/map_assets/ball_open.png", QPointF(1050, 520), QSize(72, 24));
    boxItem = createGraphicsItem(":/hud/battlehud_assets/dialogue_box.png", QPointF(906, 670), QSize(280, 60));

    gui->map()->addItem(oldMenItem);
    gui->map()->addItem(ballsItem);
    gui->map()->addItem(boxItem);

    setupTextItem();

    qDebug() << "First scenario setup done.";
}

/**
 * @brief Show the next dialogue in the sequence.
 */
void Game::showNextDialogue() {
    if (currentDialogueIndex < dialogues.size()) {
        textItem->setPlainText(dialogues[currentDialogueIndex]);
        currentDialogueIndex++;
    }
    if (currentDialogueIndex >= dialogues.size()) {
        showOldMenSpeach();
    }
}

/**
 * @brief Display the old man's speech.
 */
void Game::showOldMenSpeach() {
    setScene(gui->selectPokemon(model->getFirstTeam()));
    qDebug() << "Old Man is speaking";
}

/**
 * @brief Switch the scene to the battle interface.
 */
void Game::showFight() {
    setScene(gui->battle(player->getTeam().front(), model->getData()->randompokemon()));
    QString menuText = QString::fromStdString("Let's go " + gui->battle()->getPokemon1()->getItsName() + " !");
    gui->battle()->getMenuText()->setPlainText(menuText);
}

/**
 * @brief Switch the scene to the boss battle interface.
 */
void Game::showBossFight() {
    QGraphicsPixmapItem* bossItem = new QGraphicsPixmapItem(QPixmap(":/hud/battlehud_assets/boss_image.png"));
    bossItem->setPos(QPointF(200, 5));
    bossItem->setVisible(true);

    gui->battle()->addPersonalItem(bossItem);
    setScene(gui->battle(player->getTeam().front(), getBossTeam().front()));
    gui->battle()->getRunButton()->setEnabled(false);
}

/**
 * @brief Display the fight menu.
 */
void Game::showFightMenu() {
    gui->battle()->menuFight();
}

/**
 * @brief Display the player's Pokémon moves.
 */
void Game::showMoves() {
    gui->battle()->displayMoves();
}

/**
 * @brief Handle move button clicks during battle.
 * @param button Pointer to the clicked button.
 */
void Game::onMoveButtonClicked(QAbstractButton *button) {
    int buttonId = gui->battle()->getMoveGroup()->id(button);
    battle = new Battle(gui->battle()->getPokemon1(), gui->battle()->getPokemon2(), gui->battle());

    disableBattleButtons();
    showFightMenu();

    battle->attack(gui->battle()->getPokemon1()->getItsMoves()[buttonId], gui->battle()->getPokemon2());

    QTimer::singleShot(1000, this, &Game::continueFight);
}

/**
 * @brief Continue the fight based on battle outcome or player actions.
 */
void Game::continueFight() {
    showFightMenu();
    battle->attack(gui->battle()->getPokemon2()->getItsMoves()[0], player->getTeam().front());

    QTimer::singleShot(1000, this, &Game::enableBattleButtons);

    if(gui->battle()->getPokemon1()->getHealth() <= 0) {
        handlePokemonFainted(player->getTeam().front());
    } else if(gui->battle()->getPokemon2()->getHealth() <= 0) {
        endFight(true);
    }
}

/**
 * @brief Handle running from a battle.
 */
void Game::run() {
    endFight(true);
}

/**
 * @brief End the current fight.
 * @param playerWon Boolean indicating if the player won the fight.
 */
void Game::endFight(bool playerWon) {
    if (!playerWon) {
        setScene(gui->gameOver());
        return;
    }

    generateNewOpponent();
    player->incrementWinCount();

    double playerLevel = player->getItsLevel();
    int winsRequired = (playerLevel == 1.0) ? 2 : (playerLevel == 2.0) ? 3 : 5;

    if (player->getWinCount() >= winsRequired) {
        player->setItsLevel(playerLevel + 1.0);
        player->setWinCount(0);

        std::vector<Pokemon*> newPokemons(3);
        std::generate(newPokemons.begin(), newPokemons.end(), [&]() { return model->getData()->randompokemon(); });

        if(player->getTeam().size() < 3) {
            player->addPokemon(newPokemons.front());
            setScene(gui->map());
        } else {
            handlePokemonSwap(newPokemons);
        }
    } else {
        setScene(gui->map());
    }

    qDebug() << "Level player: " << player->getItsLevel();
    qDebug() << "Wins player: " << player->getWinCount();
}

/**
 * @brief Generate a new opponent Pokémon.
 */
void Game::generateNewOpponent() {
    Pokemon* newOpponent = model->getData()->randompokemon();
    gui->battle()->setPokemon(player->getTeam().front(), newOpponent);
}

/**
 * @brief Switch to the Pokémon selection scene.
 */
void Game::switchPokemon() {
    setScene(gui->selectPokemon(player->getTeam()));
}

/**
 * @brief Change the player's active Pokémon.
 * @param pokemon Pointer to the new Pokémon.
 */
void Game::changePokemon(Pokemon* pokemon) {
    if(player->getTeam().empty()) {
        player->addPokemon(pokemon);
        qDebug() << pokemon->getItsName();
        setScene(gui->map());
        gui->map()->removeItem(textItem);
        gui->map()->removeItem(boxItem);
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

/**
 * @brief Setup connections for player encounters and button clicks.
 */
void Game::setupConnections() {
    connect(gui->map()->getPlayer(), &Player::startEncounterCombat, this, &Game::showFight);
    connect(gui->map()->getPlayer(), &Player::startEncouterBoss, this, &Game::showBossFight);
    connect(gui->battle()->getAttackButton(), &QPushButton::clicked, this, &Game::showMoves);
    connect(gui->battle()->getPokemonButton(), &QPushButton::clicked, this, &Game::switchPokemon);
    connect(gui->battle()->getMoveGroup(), &QButtonGroup::buttonClicked, this, &Game::onMoveButtonClicked);
    connect(gui->battle()->getBackButton(), &QPushButton::clicked, this, &Game::showFightMenu);
    connect(gui->battle()->getRunButton(), &QPushButton::clicked, this, &Game::run);
    connect(gui->team(), &PlayerHUD::pokemonSelected, this, &Game::changePokemon);
}

/**
 * @brief Reset the game to its initial state.
 */
void Game::resetGame() {
    player->setItsLevel(1.0);
    player->setWinCount(0);
    player->setTeam({});
    player->setPos(200, 950);
    setScene(gui->mainMenu());
}

/**
 * @brief Create a QGraphicsPixmapItem.
 * @param pixmapPath Path to the pixmap resource.
 * @param pos Position of the item.
 * @param size Optional size to scale the pixmap.
 * @return Pointer to the created QGraphicsPixmapItem.
 */
QGraphicsPixmapItem* Game::createGraphicsItem(const QString &pixmapPath, const QPointF &pos, const QSize &size = QSize()) {
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(pixmapPath).scaled(size));
    item->setPos(pos);
    item->setZValue(10);
    return item;
}

/**
 * @brief Setup the text item for displaying dialogues.
 */
void Game::setupTextItem() {
    QString fontFamily;
    int fontId = QFontDatabase::addApplicationFont(":/hud/battlehud_assets/Minecraft.ttf");
    fontFamily = (fontId == -1) ? "Arial" : QFontDatabase::applicationFontFamilies(fontId).at(0);

    QFont customFont(fontFamily, 9);
    textItem = new QGraphicsTextItem("", boxItem);
    textItem->setPos(QPointF(8, 4));
    textItem->setDefaultTextColor(Qt::black);
    textItem->setFont(customFont);
    textItem->setTextWidth(256);
}

/**
 * @brief Disable battle buttons.
 */
void Game::disableBattleButtons() {
    gui->battle()->getAttackButton()->setEnabled(false);
    gui->battle()->getRunButton()->setEnabled(false);
    gui->battle()->getPokemonButton()->setEnabled(false);
}

/**
 * @brief Enable battle buttons.
 */
void Game::enableBattleButtons() {
    gui->battle()->getAttackButton()->setEnabled(true);
    gui->battle()->getRunButton()->setEnabled(true);
    gui->battle()->getPokemonButton()->setEnabled(true);
}

/**
 * @brief Handle the event when a Pokémon faints.
 * @param faintedPokemon Pointer to the fainted Pokémon.
 */
void Game::handlePokemonFainted(Pokemon* faintedPokemon) {
    player->removePokemon(faintedPokemon);
    if (!player->getTeam().empty()) {
        changePokemon(player->getTeam().front());
    } else {
        setScene(gui->gameOver());
    }
}

/**
 * @brief Handle swapping Pokémon when the player's team is full.
 * @param newPokemons Vector of pointers to the new Pokémon.
 */
void Game::handlePokemonSwap(const std::vector<Pokemon*>& newPokemons) {
    gui->team()->setPokemonLabel(new QGraphicsTextItem("Veuillez sélectionner un Pokémon à échanger"));
    gui->team()->setPokemons(newPokemons, player->getItsLevel());
    gui->team()->setSelectionMode(true);
    setScene(gui->team());

    connect(gui->team(), &PlayerHUD::pokemonSelected, this, [=](Pokemon* newPokemon) {
        selectedNewPokemon = newPokemon;
        disconnect(gui->team(), &PlayerHUD::pokemonSelected, this, nullptr);

        gui->team()->setPokemonLabel(new QGraphicsTextItem("Veuillez sélectionner un Pokémon à retirer"));
        gui->team()->setPokemons(player->getTeam(), player->getItsLevel());
        gui->team()->setSelectionMode(true);
        setScene(gui->team());

        connect(gui->team(), &PlayerHUD::pokemonSelected, this, [=](Pokemon* oldPokemon) {
            disconnect(gui->team(), &PlayerHUD::pokemonSelected, this, nullptr);
            player->removePokemon(oldPokemon);
            player->addPokemon(selectedNewPokemon);
            setScene(gui->map());
        });
    });
}
