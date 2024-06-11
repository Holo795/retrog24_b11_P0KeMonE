#include "battlehud.h"
#include "hoverbutton.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QButtonGroup>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QFontDatabase>

/**
 * @brief Constructs a BattleHUD scene with an optional parent.
 * @param parent The parent QObject, default is nullptr.
 */
BattleHUD::BattleHUD(QObject *parent) : QGraphicsScene(parent) {
    setObjectName("BattleHUD");
    setSceneRect(0, 0, 478, 318);

    moveButtonsGroup = new QButtonGroup(this);

    // Load and position the background image
    QGraphicsPixmapItem* background = createPixmapItem(":/hud/battlehud_assets/battleHUD-background.png", QSize(480, 240), QPoint(0, 0));

    int buttonWidth = 105;
    int buttonHeight = 40;

    // Initialize the buttons with images and dimensions
    attackButton = createButton(":/hud/battlehud_assets/fight_button.png", buttonWidth, buttonHeight, QPoint(270, 240));
    pokemonButton = createButton(":/hud/battlehud_assets/pokemon_button.png", buttonWidth, buttonHeight, QPoint(375, 240));
    runButton = createButton(":/hud/battlehud_assets/run_button.png", buttonWidth, buttonHeight, QPoint(322, 280));
    backButton = createButton(":/hud/battlehud_assets/back_button.png", buttonWidth, buttonHeight, QPoint(375, 240));
    backButton->setVisible(false);

    // Initialize the dialogue box
    dialogueBox = createPixmapItem(":/hud/battlehud_assets/dialogue_box.png", QSize(270, 80), QPoint(0, 240));

    // Add elements to the scene
    addItem(dialogueBox);
    addItem(background);
    addWidget(attackButton);
    addWidget(pokemonButton);
    addWidget(runButton);
    addWidget(backButton);

    pokemon1Item = createPixmapItem(QPoint(20, 70));
    pokemon2Item = createPixmapItem(QPoint(300, 30));

    // Load custom font
    int fontId = QFontDatabase::addApplicationFont(":/hud/battlehud_assets/Minecraft.ttf");
    if (fontId == -1) {
        qDebug() << "Failed to load Minecraft font.";
    }
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 15);

    health1 = createTextItem(Qt::white, customFont, QPoint(80, 100));
    health2 = createTextItem(Qt::white, customFont, QPoint(320, 30));

    attackText = createTextItem(Qt::white, customFont, QPoint(10, 260));
    menuText = createTextItem(Qt::white, customFont, QPoint(10, 255));
    menuText->setTextWidth(250);

    // Add Pokémon images and health displays to the scene
    addItem(pokemon1Item);
    addItem(pokemon2Item);
    addItem(health1);
    addItem(health2);
    addItem(menuText);
    addItem(attackText);
}

/**
 * @brief Destructor for the BattleHUD class.
 */
BattleHUD::~BattleHUD()
{
    // No need to delete widgets if they have a parent set
}

/**
 * @brief Retrieves the attack button.
 * @return A pointer to the QPushButton used for attacks.
 */
QPushButton *BattleHUD::getAttackButton() const
{
    return attackButton;
}

/**
 * @brief Retrieves the pokemon button.
 * @return A pointer to the QPushButton used for changing pokemon.
 */
QPushButton *BattleHUD::getPokemonButton() const
{
    return pokemonButton;
}

/**
 * @brief Retrieves the run button.
 * @return A pointer to the QPushButton used for leaving the battle.
 */
QPushButton *BattleHUD::getRunButton() const
{
    return runButton;
}

/**
 * @brief Retrieves the back button.
 * @return A pointer to the QPushButton used for going back.
 */
QPushButton *BattleHUD::getBackButton() const
{
    return backButton;
}

/**
 * @brief Retrieves the menu text item.
 * @return A pointer to the QGraphicsTextItem used for displaying menu text.
 */
QGraphicsTextItem* BattleHUD::getMenuText() const {
    return menuText;
}

/**
 * @brief Retrieves the move buttons group.
 * @return A pointer to the QButtonGroup for move buttons.
 */
QButtonGroup *BattleHUD::getMoveGroup() const
{
    return moveButtonsGroup;
}

/**
 * @brief Retrieves the first Pokémon shown in the HUD.
 * @return A constant pointer to the first Pokémon.
 */
Pokemon *BattleHUD::getPokemon1() const
{
    return pokemon1;
}

/**
 * @brief Retrieves the second Pokémon shown in the HUD.
 * @return A constant pointer to the second Pokémon.
 */
Pokemon *BattleHUD::getPokemon2() const
{
    return pokemon2;
}

/**
 * @brief Updates the displayed Pokémon and their health on the HUD.
 * @param pk1 Pointer to the first Pokémon.
 * @param pk2 Pointer to the second Pokémon.
 */
void BattleHUD::setPokemon(Pokemon *pk1, Pokemon *pk2) {
    pokemon1 = pk1;
    pokemon2 = pk2;
    updatePokemonGraphics(pokemon1Item, pk1, true);
    updatePokemonGraphics(pokemon2Item, pk2, false);

    QString healthText1 = QString::number(pk1->getHealth()) + "/" + QString::number(pk1->getItsMaxHealth());
    health1->setPlainText(healthText1);

    QString healthText2 = QString::number(pk2->getHealth()) + "/" + QString::number(pk2->getItsMaxHealth());
    health2->setPlainText(healthText2);

    qDebug() << healthText2; // Debug output to trace health updates
}

/**
 * @brief Shakes the Pokémon's image on the HUD.
 * @param pk Pointer to the Pokémon to shake.
 */
void BattleHUD::shakePokemon(Pokemon *pk) {
    QGraphicsPixmapItem *pokemonItem = (pk == pokemon1) ? pokemon1Item : pokemon2Item;
    applyShakeAnimation(pokemonItem, 700, 500);
}

/**
 * @brief Dashes the Pokémon's image on the HUD.
 * @param pk Pointer to the Pokémon to dash.
 */
void BattleHUD::frontDashPokemon(Pokemon *pk) {
    QGraphicsPixmapItem *pokemonItem = (pk == pokemon1) ? pokemon1Item : pokemon2Item;
    if (pokemonItem) {
        applyDashAnimation(pokemonItem, 500, (pk == pokemon1) ? QPointF(10, -10) : QPointF(-10, 10));
    }
}

/**
 * @brief Displays the available moves from pokemon 1 as buttons.
 */
void BattleHUD::displayMoves()
{
    attackButton->setVisible(false);
    pokemonButton->setVisible(false);
    runButton->setVisible(false);
    dialogueBox->setVisible(false);
    menuText->setVisible(false);

    clearMoveButtons();

    int buttonWidth = 160;
    int buttonHeight = 40;
    QPoint positions[] = { QPoint(0, 240), QPoint(160, 240), QPoint(0, 280), QPoint(160, 280) };

    for(int i = 0; i < pokemon1->getItsMoves().size() && i < 4; ++i) {
        createMoveButton(pokemon1->getItsMoves().at(i), positions[i], buttonWidth, buttonHeight, i);
    }

    backButton->setVisible(true);

    qDebug() << "Number of buttons in moveButtonsGroup: " << moveButtonsGroup->buttons().size();
}

/**
 * @brief Shows the fight menu with attack, pokemon, and run buttons.
 */
void BattleHUD::menuFight() {
    backButton->setVisible(false);
    // Hide move buttons
    for (QAbstractButton *button : moveButtonsGroup->buttons()) {
        button->setVisible(false);
    }

    getRunButton()->isEnabled() ? getRunButton()->setEnabled(true) : getRunButton()->setEnabled(false);

    // Show dialogue box and action buttons
    dialogueBox->setVisible(true);
    attackButton->setVisible(true);
    pokemonButton->setVisible(true);
    runButton->setVisible(true);
}

/**
 * @brief Sets the text to be displayed in the menu text item.
 * @param text The text to display.
 */
void BattleHUD::setText(const QString &text) {
    qDebug() << "Setting text to:" << text;
    menuText->setVisible(true); // Ensure menuText is visible
    menuText->setPlainText(text);
    qDebug() << "menuText content:" << menuText->toPlainText();
    update(); // Ensure the scene is updated if necessary
}

/**
 * @brief Adds a custom QGraphicsPixmapItem to the scene.
 * @param item Pointer to the QGraphicsPixmapItem to add.
 */
void BattleHUD::addPersonalItem(QGraphicsPixmapItem* item) {
    addItem(item);
}

// Helper methods

/**
 * @brief Creates a pixmap item from a given image path and size.
 * @param path The path to the image.
 * @param size The desired size of the pixmap.
 * @param pos The position to place the pixmap.
 * @return A pointer to the created QGraphicsPixmapItem.
 */
QGraphicsPixmapItem* BattleHUD::createPixmapItem(const QString &path, const QSize &size, const QPoint &pos) {
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap(path).scaled(size));
    item->setPos(pos);
    return item;
}

/**
 * @brief Creates an empty pixmap item at a given position.
 * @param pos The position to place the pixmap item.
 * @return A pointer to the created QGraphicsPixmapItem.
 */
QGraphicsPixmapItem* BattleHUD::createPixmapItem(const QPoint &pos) {
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
    item->setPos(pos);
    return item;
}

/**
 * @brief Creates a button with a given image path, size, and position.
 * @param path The path to the button image.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param pos The position to place the button.
 * @return A pointer to the created QPushButton.
 */
QPushButton* BattleHUD::createButton(const QString &path, int width, int height, const QPoint &pos) {
    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(QPixmap(path)));
    button->setIconSize(QSize(width, height));
    button->setFixedSize(width, height);
    button->setGeometry(pos.x(), pos.y(), width, height);
    return button;
}

/**
 * @brief Creates a text item with a given color, font, and position.
 * @param color The color of the text.
 * @param font The font of the text.
 * @param pos The position to place the text item.
 * @return A pointer to the created QGraphicsTextItem.
 */
QGraphicsTextItem* BattleHUD::createTextItem(const QColor &color, const QFont &font, const QPoint &pos) {
    QGraphicsTextItem* item = new QGraphicsTextItem();
    item->setDefaultTextColor(color);
    item->setFont(font);
    item->setPos(pos);
    return item;
}

/**
 * @brief Updates the graphics of a Pokémon item.
 * @param item The QGraphicsPixmapItem representing the Pokémon.
 * @param pk The Pokémon object.
 * @param isBack Whether the Pokémon is shown from the back.
 */
void BattleHUD::updatePokemonGraphics(QGraphicsPixmapItem* item, Pokemon* pk, bool isBack) {
    QString path = QString(":/sprites/pk_sprites/") + QString::number(pk->getId()) + (isBack ? "_back.png" : "_front.png");
    item->setPixmap(QPixmap(path).scaled(200, 200));
}

/**
 * @brief Applies a shake animation to a given pixmap item.
 * @param item The QGraphicsPixmapItem to animate.
 * @param totalDuration The duration of the animation in milliseconds.
 * @param delay The delay before the animation starts.
 */
void BattleHUD::applyShakeAnimation(QGraphicsPixmapItem* item, int totalDuration, int delay) {
    QTimeLine* timeLine = new QTimeLine(totalDuration, this);
    timeLine->setLoopCount(1);

    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
    animation->setItem(item);
    animation->setTimeLine(timeLine);

    double startTime = delay / static_cast<double>(totalDuration);
    int steps = 20;
    double interval = 50.0 / totalDuration;

    for (int i = 0; i <= steps; ++i) {
        double t = startTime + i * interval;
        if (t > 1.0) break;

        QPointF direction = (i == 0) ? QPointF(10, 0) : item->pos() - animation->posAt(t - interval);
        animation->setPosAt(t, item->pos() + direction);
    }
    animation->setPosAt(1.0, item->pos());

    connect(timeLine, &QTimeLine::finished, timeLine, &QTimeLine::deleteLater);
    connect(timeLine, &QTimeLine::finished, animation, &QGraphicsItemAnimation::deleteLater);

    timeLine->start();
}

/**
 * @brief Applies a dash animation to a given pixmap item.
 * @param item The QGraphicsPixmapItem to animate.
 * @param duration The duration of the animation in milliseconds.
 * @param increment The position increment for the dash.
 */
void BattleHUD::applyDashAnimation(QGraphicsPixmapItem* item, int duration, const QPointF& increment) {
    QTimeLine* timeLine = new QTimeLine(duration, this);
    timeLine->setLoopCount(1);

    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
    animation->setItem(item);
    animation->setTimeLine(timeLine);

    int steps = 6;
    for (int i = 0; i <= steps; ++i) {
        double t = i / static_cast<double>(steps);
        animation->setPosAt(t, item->pos() + increment * (t * 10));
    }
    animation->setPosAt(1.0, item->pos());

    connect(timeLine, &QTimeLine::finished, timeLine, &QTimeLine::deleteLater);
    connect(timeLine, &QTimeLine::finished, animation, &QGraphicsItemAnimation::deleteLater);

    timeLine->start();
}

/**
 * @brief Clears all move buttons from the scene.
 */
void BattleHUD::clearMoveButtons() {
    for(QAbstractButton *button : moveButtonsGroup->buttons()) {
        moveButtonsGroup->removeButton(button);
        button->deleteLater();
    }
}

/**
 * @brief Creates a move button for a given move and position.
 * @param move The move to create the button for.
 * @param pos The position to place the button.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param id The ID of the move button.
 */
void BattleHUD::createMoveButton(Move* move, const QPoint &pos, int width, int height, int id) {
    QPixmap defaultPixmap(":/hud/battlehud_assets/" + QString::number(move->getItsType()) + "Button.png");
    QPixmap hoverPixmap(":/hud/battlehud_assets/" + QString::number(move->getItsType()) + "Button_hover.png");

    HoverButton *moveButton = new HoverButton(defaultPixmap, hoverPixmap);
    moveButton->setIcon(QIcon(defaultPixmap.scaled(width, height)));
    moveButton->setGeometry(pos.x(), pos.y(), width, height);
    moveButton->setIconSize(QSize(width, height));
    moveButton->setStyleSheet("background: transparent;");

    QLabel *moveLabel = new QLabel(QString::fromStdString(move->getItsName()), moveButton);
    moveLabel->setGeometry(0, 0, width, height);
    moveLabel->setAlignment(Qt::AlignCenter);
    moveLabel->setStyleSheet("QLabel { color: white; font: bold 14px; }");
    moveLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    // Set tooltip for the move button
    moveButton->setToolTip("Nom: " + QString::fromStdString(move->getItsName()) + "<br>"
                           + "Type: " +  QString::fromStdString(move->getItsTextType(move->getItsType())) + "<br>"
                           + "Puissance: " + QString::number(move->getItsPower()));

    addWidget(moveButton);
    moveButtonsGroup->addButton(moveButton, id);
}
