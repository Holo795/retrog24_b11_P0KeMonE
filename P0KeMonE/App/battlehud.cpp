#include "battlehud.h"

#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QGraphicsTextItem>

#include "pokemon.h"


BattleHUD::BattleHUD(Pokemon *pk1, Pokemon *pk2, QObject *parent) : QGraphicsScene(parent) {

    setObjectName("BattleHUD");
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(QPixmap(":/battleHUD/battleHUD-background.png").scaled(480, 240));
    background->setPos(0, 0);

    // Create and configure the attack button
    QPushButton *attackButton = new QPushButton();
    QPixmap buttonImage(":/battleHUD/fight_button.png.opdownload");
    attackButton->setIcon(QIcon(buttonImage));

    int buttonWidth = 105;
    int buttonHeight = 40;
    attackButton->setIconSize(QSize(buttonWidth, buttonHeight));
    attackButton->setFixedSize(buttonWidth, buttonHeight);
    attackButton->setGeometry(190, 250, buttonWidth, buttonHeight);


    QString fulllifePK1 = QString::number(pk1->getHealth());
    QString fulllifePK2 = QString::number(pk2->getHealth());



    QGraphicsPixmapItem *pokemon1Item = new QGraphicsPixmapItem(QPixmap(":/pokemons/pk_sprite/" + QString::number(pk1->getId()) + "_front.png").scaled(200, 200));
    pokemon1Item->setPos(20, 70);

    QGraphicsPixmapItem *pokemon2Item = new QGraphicsPixmapItem(QPixmap(":/pokemons/pk_sprite/" + QString::number(pk2->getId()) + "_front.png"));
    pokemon2Item->setPos(300, 30);

    QString healthText1 = QString::number(pk1->getHealth()) + "/" + fulllifePK1;

    QGraphicsTextItem *health1 = new QGraphicsTextItem(healthText1);
    QFont promptFont("Arial", 15);
    health1->setFont(promptFont);
    health1->setPos(80, 100);

    QString healthText2 = QString::number(pk2->getHealth()) + "/" + fulllifePK2;

    QGraphicsTextItem *health2 = new QGraphicsTextItem(healthText2);
    health2->setFont(promptFont);
    health2->setPos(320, 30);

    addItem(background);
    addWidget(attackButton);
    addItem(pokemon1Item);
    addItem(pokemon2Item);
    addItem(health1);
    addItem(health2);

}
