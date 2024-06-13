#include "battlehud.h"
#include "hoverbutton.h"
#include "pokemon.h"

BattleHUD::BattleHUD(QObject *parent) : QGraphicsScene(parent) {
    setObjectName("BattleHUD");
    setSceneRect(0, 0, 478, 318);

    moveButtonsGroup = new QButtonGroup(this);
    //remove background of move buttons

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


    oldMenPixmap = createPixmapItem(":/hud/battlehud_assets/oldMen_image.png", QSize(64,124), QPoint(200, 5));

    bossPixmap = createPixmapItem(":/hud/battlehud_assets/boss_image.png", QSize(100,114), QPoint(200, 5));
    bossPixmap->setVisible(false);

    QFont minecraftFont("Minecraft", 15);

    health1 = createTextItem(Qt::white, minecraftFont, QPoint(80, 100));
    health2 = createTextItem(Qt::white, minecraftFont, QPoint(320, 30));


    attackText = createTextItem(Qt::white, minecraftFont, QPoint(10, 260));
    menuText = createTextItem(Qt::white, minecraftFont, QPoint(10, 255));
    menuText->setTextWidth(250);

    // Add Pokemon images and health displays to the scene
    addItem(pokemon1Item);
    addItem(pokemon2Item);
    addItem(health1);
    addItem(health2);
    addItem(menuText);
    addItem(attackText);
    addItem(oldMenPixmap);
    addItem(bossPixmap);
}

BattleHUD::~BattleHUD()
{
    // No need to delete widgets if they have a parent set
}

QPushButton *BattleHUD::getPokemonButton()
{
    return pokemonButton;
}

QPushButton *BattleHUD::getRunButton()
{
    return runButton;
}


void BattleHUD::setPokemon(Pokemon *pk1, Pokemon *pk2) {
    pokemon1 = pk1;
    pokemon2 = pk2;
    updatePokemonGraphics(pokemon1Item, pk1, true);
    updatePokemonGraphics(pokemon2Item, pk2, false);

    QString healthText1 = QString::number(pk1->getHealth()) + "/" + QString::number(pk1->getItsMaxHealth());
    health1->setPlainText(healthText1);

    QString healthText2 = QString::number(pk2->getHealth()) + "/" + QString::number(pk2->getItsMaxHealth());
    health2->setPlainText(healthText2);

    /*QString menuTextText = QString::fromStdString("Let's go " + pk1->getItsName() + "!");
    menuText->setPlainText(menuTextText);*/

    qDebug() << healthText2; // Debug output to trace health updates
}

void BattleHUD::shakePokemon(Pokemon *pk) {
    QGraphicsPixmapItem *pokemonItem = (pk == pokemon1) ? pokemon1Item : pokemon2Item;
    applyShakeAnimation(pokemonItem, 700, 500);
}

void BattleHUD::frontDashPokemon(Pokemon *pk) {
    QGraphicsPixmapItem *pokemonItem = (pk == pokemon1) ? pokemon1Item : pokemon2Item;
    if (pokemonItem) {
        applyDashAnimation(pokemonItem, 500, (pk == pokemon1) ? QPointF(10, -10) : QPointF(-10, 10));
    }
}

QPushButton *BattleHUD::getAttackButton()
{
    return attackButton;
}

Pokemon *BattleHUD::getPokemon1() const
{
    return pokemon1;
}

Pokemon *BattleHUD::getPokemon2() const
{
    return pokemon2;
}

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


void BattleHUD::menuFight() {
    backButton->setVisible(false);
    // Masquer les boutons de déplacement
    for (QAbstractButton *button : moveButtonsGroup->buttons()) {
        button->setVisible(false);
    }


    getRunButton()->isEnabled() ? getRunButton()->setEnabled(true) : getRunButton()->setEnabled(false);

    // Afficher le texte
    dialogueBox->setVisible(true);
    attackButton->setVisible(true);
    pokemonButton->setVisible(true);
    runButton->setVisible(true);
}

void BattleHUD::setText(string text) {
    qDebug() << "Setting text to:" << text;
    menuText->setVisible(true); // Assurez-vous que menuText est visible
    menuText->setPlainText(QString::fromStdString(text));
    qDebug() << "menuText content:" << menuText->toPlainText();
    update(); // Assurez-vous de mettre à jour la scène si nécessaire
}

void BattleHUD::addPersonalItem(QGraphicsPixmapItem* item) {
    addItem(item);
}

QButtonGroup *BattleHUD::getMoveGroup() const
{
    return moveButtonsGroup;
}

QPushButton *BattleHUD::getBackButton() const
{
    return backButton;
}

// Helper methods

QGraphicsPixmapItem* BattleHUD::createPixmapItem(const QString &path, const QSize &size, const QPoint &pos) {
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap(path).scaled(size));
    item->setPos(pos);
    return item;
}

QGraphicsPixmapItem* BattleHUD::createPixmapItem(const QPoint &pos) {
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
    item->setPos(pos);
    return item;
}

QPushButton* BattleHUD::createButton(const QString &path, int width, int height, const QPoint &pos) {
    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(QPixmap(path)));
    button->setIconSize(QSize(width, height));
    button->setFixedSize(width, height);
    button->setGeometry(pos.x(), pos.y(), width, height);
    return button;
}

QGraphicsTextItem* BattleHUD::createTextItem(const QColor &color, const QFont &font, const QPoint &pos) {
    QGraphicsTextItem* item = new QGraphicsTextItem();
    item->setDefaultTextColor(color);
    item->setFont(font);
    item->setPos(pos);
    return item;
}

void BattleHUD::updatePokemonGraphics(QGraphicsPixmapItem* item, Pokemon* pk, bool isBack) {
    QString path = QString(":/sprites/pk_sprites/") + QString::number(pk->getId()) + (isBack ? "_back.png" : "_front.png");
    item->setPixmap(QPixmap(path).scaled(200, 200));
}

void BattleHUD::applyShakeAnimation(QGraphicsPixmapItem* item, int totalDuration, int delay) {
    QTimeLine* timeLine = new QTimeLine(totalDuration, this);
    timeLine->setLoopCount(1);

    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
    animation->setItem(item);
    animation->setTimeLine(timeLine);

    double startTime = delay / static_cast<double>(totalDuration);
    double interval = 50.0 / totalDuration;

    for (double t = startTime; t <= 1.0; t += interval) {
        QPointF direction = (t == startTime) ? QPointF(10, 0) : item->pos() - animation->posAt(t - interval);
        animation->setPosAt(t, item->pos() + direction);
    }
    animation->setPosAt(1.0, item->pos());

    connect(timeLine, &QTimeLine::finished, timeLine, &QTimeLine::deleteLater);
    connect(timeLine, &QTimeLine::finished, animation, &QGraphicsItemAnimation::deleteLater);

    timeLine->start();
}

void BattleHUD::applyDashAnimation(QGraphicsPixmapItem* item, int duration, const QPointF &increment) {
    QTimeLine* timeLine = new QTimeLine(duration, this);
    timeLine->setLoopCount(1);

    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
    animation->setItem(item);
    animation->setTimeLine(timeLine);

    for (double t = 0.0; t <= 0.6; t += 0.1) {
        animation->setPosAt(t, item->pos() + increment * (t * 10));
    }
    animation->setPosAt(1.0, item->pos());

    connect(timeLine, &QTimeLine::finished, timeLine, &QTimeLine::deleteLater);
    connect(timeLine, &QTimeLine::finished, animation, &QGraphicsItemAnimation::deleteLater);
    timeLine->start();
}

void BattleHUD::clearMoveButtons() {
    for(QAbstractButton *button : moveButtonsGroup->buttons()) {
        moveButtonsGroup->removeButton(button);
        button->deleteLater();
    }
}

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
    moveButton->setToolTip("Name : " + QString::fromStdString(move->getItsName()) + "<br>"
                        + "Power : " + QString::number(move->getItsPower()) + "<br>"
                        + "Accuracy : " + QString::number(move->getItsAccuracy()) + "<br>"
                        + "Nature : " +  QString::fromStdString(move->getItsTextType(move->getItsNature())) + "<br>"
                        + "Type : " +  QString::fromStdString(move->getItsTextType(move->getItsType())) + "<br>");

    addWidget(moveButton);
    moveButtonsGroup->addButton(moveButton, id);
}

void BattleHUD::enableBattleButtons(bool exitButton) {
    attackButton->setEnabled(true);
    runButton->setEnabled(exitButton);
    pokemonButton->setEnabled(true);
}

void BattleHUD::disableBattleButtons(bool exitButton) {
    attackButton->setEnabled(false);
    runButton->setEnabled(!exitButton);
    pokemonButton->setEnabled(false);
}


QGraphicsPixmapItem* BattleHUD::getOldMenPixmap(){
    return oldMenPixmap;
}

QGraphicsPixmapItem* BattleHUD::getBossPixmap(){
    return bossPixmap;
}
