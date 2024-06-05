#include "battlehud.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

#include "pokemon.h"

/**
 * Constructor for the BattleHUD class. Initializes the HUD with a background, Pokémon images,
 * health displays, and an attack button.
 */
BattleHUD::BattleHUD(QObject *parent) : QGraphicsScene(parent) {
    setObjectName("BattleHUD");
    // Load and position the background image
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(QPixmap(":/battleHUD/battleHUD-background.png").scaled(480, 240));
    background->setPos(0, 0);

    // Initialize the attack button with an image and dimensions
    attackButton = new QPushButton();
    QPixmap buttonImage(":/battleHUD/fight_button.png.opdownload");
    attackButton->setIcon(QIcon(buttonImage));

    int buttonWidth = 105;
    int buttonHeight = 40;
    attackButton->setIconSize(QSize(buttonWidth, buttonHeight));
    attackButton->setFixedSize(buttonWidth, buttonHeight);
    attackButton->setGeometry(190, 250, buttonWidth, buttonHeight);

    // Add elements to the scene
    addItem(background);
    addWidget(attackButton);
    pokemon1Item = new QGraphicsPixmapItem();
    pokemon1Item->setPos(20, 70);

    pokemon2Item = new QGraphicsPixmapItem();
    pokemon2Item->setPos(300, 30);

    health1 = new QGraphicsTextItem();
    QFont promptFont("Arial", 15);
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
 * Returns the QPushButton used for initiating attacks.
 */
QPushButton *BattleHUD::getAttackButton()
{
    return attackButton;
}

/**
 * Updates the displayed Pokémon images and their health statistics on the HUD.
 */
void BattleHUD::setPokemon(Pokemon *pk1, Pokemon *pk2) {
    pokemon1 = pk1;
    pokemon2 = pk2;
    pokemon1Item->setPixmap(QPixmap(":/pokemons/pk_sprite/" + QString::number(pk1->getId()) + "_front.png").scaled(200, 200));
    pokemon2Item->setPixmap(QPixmap(":/pokemons/pk_sprite/" + QString::number(pk2->getId()) + "_front.png"));

    QString fulllifePK1 = QString::number(pk1->getItsMaxHealth());
    QString fulllifePK2 = QString::number(pk2->getItsMaxHealth());

    QString healthText1 = QString::number(pk1->getHealth()) + "/" + fulllifePK1;
    health1->setPlainText(healthText1);

    QString healthText2 = QString::number(pk2->getHealth()) + "/" + fulllifePK2;
    health2->setPlainText(healthText2);

    qDebug() << healthText2; // Debug output to trace health updates
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
