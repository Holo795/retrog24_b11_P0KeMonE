#include "battlehud.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QButtonGroup>

#include "pokemon.h"

/**
 * Constructor for the BattleHUD class. Initializes the HUD with a background, Pokémon images,
 * health displays, and an attack button.
 */
BattleHUD::BattleHUD(QObject *parent) : QGraphicsScene(parent) {
    setObjectName("BattleHUD");
    // Load and position the background image
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(QPixmap(":/hud/battlehud_assets/battleHUD-background.png").scaled(480, 240));
    background->setPos(0, 0);

    int buttonWidth = 105;
    int buttonHeight = 40;

    // Initialize the attack button with an image and dimensions
    attackButton = new QPushButton();
    QPixmap buttonImage1(":/hud/battlehud_assets/fight_button.png");
    attackButton->setIcon(QIcon(buttonImage1));

    pokemonButton = new QPushButton();
    QPixmap buttonImage2(":/hud/battlehud_assets/pokemon_button.png");
    pokemonButton->setIcon(QIcon(buttonImage2));

    runButton = new QPushButton();
    QPixmap buttonImage3(":/hud/battlehud_assets/run_button.png");
    runButton->setIcon(QIcon(buttonImage3));

    attackButton->setIconSize(QSize(buttonWidth, buttonHeight));
    attackButton->setFixedSize(buttonWidth, buttonHeight);
    attackButton->setGeometry(270, 240, buttonWidth, buttonHeight);

    pokemonButton->setIconSize(QSize(buttonWidth, buttonHeight));
    pokemonButton->setFixedSize(buttonWidth, buttonHeight);
    pokemonButton->setGeometry(375, 240, buttonWidth, buttonHeight);

    runButton->setIconSize(QSize(buttonWidth, buttonHeight));
    runButton->setFixedSize(buttonWidth, buttonHeight);
    runButton->setGeometry(322, 280, buttonWidth, buttonHeight);


    // Initailize the moves buttons and texte dialogue box
    dialogueBox = new QGraphicsPixmapItem(QPixmap(":/hud/battlehud_assets/dialogue_box.png").scaled(270, 80));
    dialogueBox->setPos(0, 240);


    // Add elements to the scene
    addItem(dialogueBox);
    addItem(background);
    addWidget(attackButton);
    addWidget(pokemonButton);
    addWidget(runButton);
    pokemon1Item = new QGraphicsPixmapItem();
    pokemon1Item->setPos(20, 70);

    pokemon2Item = new QGraphicsPixmapItem();
    pokemon2Item->setPos(300, 30);

    QFont promptFont("Arial", 15);
    health1 = new QGraphicsTextItem();
    health1->setDefaultTextColor(Qt::white);
    health1->setFont(promptFont);
    health1->setPos(80, 100);

    health2 = new QGraphicsTextItem();
    health2->setDefaultTextColor(Qt::white);
    health2->setFont(promptFont);
    health2->setPos(320, 30);

    // Add Pokémon images and health displays to the scene
    addItem(pokemon1Item);
    addItem(pokemon2Item);
    addItem(health1);
    addItem(health2);
}

/**
 * Destructor for the BattleHUD.
 */
BattleHUD::~BattleHUD()
{
    delete attackButton;
    delete pokemon1Item;
    delete pokemon2Item;
    delete health1;
    delete health2;
}

/**
 * Returns the QPushButton used for switching pokemon.
 */
QPushButton *BattleHUD::getPokemonButton()
{
    return pokemonButton;
}

/**
 * Returns the QPushButton used for leaving the battle.
 */
QPushButton *BattleHUD::getRunButton()
{
    return runButton;
}

/**
 * Updates the displayed Pokémon images and their health statistics on the HUD.
 */
void BattleHUD::setPokemon(Pokemon *pk1, Pokemon *pk2) {
    pokemon1 = pk1;
    pokemon2 = pk2;
    pokemon1Item->setPixmap(QPixmap(":/sprites/pk_sprites/" + QString::number(pk1->getId()) + "_back.png").scaled(200, 200));
    pokemon2Item->setPixmap(QPixmap(":/sprites/pk_sprites/" + QString::number(pk2->getId()) + "_front.png"));

    QString fulllifePK1 = QString::number(pk1->getItsMaxHealth());
    QString fulllifePK2 = QString::number(pk2->getItsMaxHealth());

    QString healthText1 = QString::number(pk1->getHealth()) + "/" + fulllifePK1;
    health1->setPlainText(healthText1);

    QString healthText2 = QString::number(pk2->getHealth()) + "/" + fulllifePK2;
    health2->setPlainText(healthText2);

    qDebug() << healthText2; // Debug output to trace health updates
}

/**
 * Shakes the Pokémon's image on the HUD.
 */
void BattleHUD::shakePokemon(Pokemon *pk) {
    // Get the associated QGraphicsPixmapItem based on which Pokemon is passed
    QGraphicsPixmapItem *pokemonItem = (pk == pokemon1) ? pokemon1Item : pokemon2Item;

    // Configure the timeline for the shake effect
    int totalDuration = 700;  // Including delay and shake duration
    QTimeLine* timeLine = new QTimeLine(totalDuration, this);
    timeLine->setLoopCount(1);  // Play the shake animation once

    // Set up the item animation
    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
    animation->setItem(pokemonItem);
    animation->setTimeLine(timeLine);

    // Define the start time for the shake and interval between position changes
    double startTime = 500.0 / totalDuration;
    double interval = 50.0 / totalDuration;

    // Set key frames for shaking the Pokemon item
    for (double t = startTime; t <= 1.0; t += interval) {
        QPointF direction = (t == startTime) ? QPointF(10, 0) : pokemonItem->pos() - animation->posAt(t - interval);
        animation->setPosAt(t, pokemonItem->pos() + direction);
    }
    animation->setPosAt(1.0, pokemonItem->pos());  // Return to original position

    // Connect the shake animation to the timeline and re-enable the attack button when done
    connect(timeLine, &QTimeLine::finished, timeLine, &QTimeLine::deleteLater);
    connect(timeLine, &QTimeLine::finished, animation, &QGraphicsItemAnimation::deleteLater);

    // Signal the shake is done
    timeLine->start();  // Start the timeline to begin the animation
}

/**
 * Animates the front Pokemon to dash forward and then return to its original position.
 */
void BattleHUD::frontDashPokemon(Pokemon *pk) {
    // Retrieve the associated QGraphicsPixmapItem for the Pokemon
    QGraphicsPixmapItem *pokemonItem = (pk == pokemon1) ? pokemon1Item : pokemon2Item;
    if (!pokemonItem) return;  // Exit if no item found

    // Setup the timeline for the dash effect
    QTimeLine* timeLine = new QTimeLine(500, this);  // Dash duration
    timeLine->setLoopCount(1);  // Play the dash animation once

    // Initialize the animation and link to the timeline
    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
    animation->setItem(pokemonItem);
    animation->setTimeLine(timeLine);

    // Calculate the movement increment based on the Pokemon
    QPointF increment = (pk == pokemon1) ? QPointF(10, -10) : QPointF(-10, 10);

    // Create key frames for the dash effect
    for (double t = 0.0; t <= 0.6; t += 0.1) {
        animation->setPosAt(t, pokemonItem->pos() + increment * (t * 10));
    }
    animation->setPosAt(1.0, pokemonItem->pos());  // End at the original position

    // Ensure clean up after the animation completes
    connect(timeLine, &QTimeLine::finished, timeLine, &QTimeLine::deleteLater);
    connect(timeLine, &QTimeLine::finished, animation, &QGraphicsItemAnimation::deleteLater);
    timeLine->start();  // Begin the animation
}

/**
 * Returns the QPushButton used for initiating attacks.
 */
QPushButton *BattleHUD::getAttackButton()
{
    return attackButton;
}

/**
 * Retrieves the first Pokémon currently displayed on the HUD.
 */
Pokemon *BattleHUD::getPokemon1() const
{
    return pokemon1;
}

/**
 * Retrieves the second Pokémon currently displayed on the HUD.
 */
Pokemon *BattleHUD::getPokemon2() const
{
    return pokemon2;
}

void BattleHUD::displayMoves(QList<Move> moves)
{

    attackButton->close();
    delete pokemonButton;
    delete runButton;
    delete dialogueBox;

    // Create and add new move buttons
    int buttonWidth = 160;
    int buttonHeight = 40;

    moveButtonsGroup = new QButtonGroup(this);

    QPoint positions[] = { QPoint(0, 240), QPoint(160, 240), QPoint(0, 280), QPoint(160, 280) };

    for(int i = 0; i < pokemon1->getItsMoves().size(); ++i) {
        if(i > 3) {
            break;
        }
        std::string typeName;
        switch(pokemon1->getItsType()) {
        case 0 :
            typeName = "grass";
            qDebug() << typeName;
            break;
        case 1 :
            typeName = "fire";
            qDebug() << typeName;
            break;
        case 2 :
            typeName = "water";
            qDebug() << typeName;
            break;
        case 3 :
            typeName = "electrik";
            qDebug() << typeName;

            break;
        case 4 :
            typeName = "ground";
            qDebug() << typeName;
            break;
        case 5 :
            typeName = "flying";
            qDebug() << typeName;
            break;
        }





        // Create and configure the move button
        QString qType = QString::fromStdString(typeName);
        QPushButton *moveButton = new QPushButton();
        moveButton->setIcon(QPixmap(":/hud/battlehud_assets/" + qType + "Button.png").scaled(buttonWidth, buttonHeight));
        moveButton->setGeometry(positions[i].x(), positions[i].y(), buttonWidth, buttonHeight);
        moveButton->setIconSize(QSize(buttonWidth, buttonHeight));
        moveButton->setFixedSize(buttonWidth, buttonHeight);

        // Set the text of the move button to the move name
        moveButton->setText(QString::fromStdString(pokemon1->getItsMoves()[0].getItsName())); // Assuming `Move` has a `getName()` method

        // Style the button to overlay text on the image
        moveButton->setStyleSheet(
            "QPushButton {"
            "    border: none;"
            "    color: white;"
            "    font: bold 12px;"
            "    text-align: center;"
            "    padding: 10px 0;"
            "}"
            "QPushButton::icon {"
            "    position: absolute;"
            "    top: 0px;"
            "    left: 0px;"
            "}"
            );

        addWidget(moveButton);
        moveButtonsGroup->addButton(moveButton, i);
    }


    QPushButton *backButton = new QPushButton();
    backButton->setIcon(QPixmap(":/hud/battlehud_assets/back_button.png").scaled(buttonWidth, buttonHeight));
    backButton->setIconSize(QSize(buttonWidth, buttonHeight));
    backButton->setFixedSize(buttonWidth, buttonHeight);
    backButton->setGeometry(320 , 240, buttonWidth, buttonHeight);
    addWidget(backButton);


}

QButtonGroup *BattleHUD::getMoveGroup()
{
    return moveButtonsGroup;
}
