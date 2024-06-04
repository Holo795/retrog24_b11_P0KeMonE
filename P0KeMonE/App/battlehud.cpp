#include "battlehud.h"


#include <QFont>
#include <QImage>
#include <QPixmap>
#include "battle.h"
#include "pokemon.h"

BattleHUD::BattleHUD(QGraphicsScene *scene) {

    this->scene = scene;

    background = new QGraphicsPixmapItem(QPixmap(":/battleHUD/battleHUD-background.png").scaled(480, 240));
    background->setPos(0, 0);

    // Create and configure the attack button
    attackButton = new QPushButton();
    QPixmap buttonImage(":/battleHUD/fight_button.png.opdownload");
    attackButton->setIcon(QIcon(buttonImage));

    int buttonWidth = 105;
    int buttonHeight = 40;
    attackButton->setIconSize(QSize(buttonWidth, buttonHeight));
    attackButton->setFixedSize(buttonWidth, buttonHeight);
    attackButton->setGeometry(190, 250, buttonWidth, buttonHeight);


    Pokemon* pokemon1 = new Pokemon(1, "zeon", PKTYPE::Plante,40, 40, 40,40, 40, 40, 1);
    Pokemon* pokemon2 = new Pokemon(2, "kylian", PKTYPE::Electrique,50, 50, 50,50, 20, 50, 1);
    QString fulllifePK1 = QString::number(pokemon1->getHealth());
    QString fulllifePK2 = QString::number(pokemon2->getHealth());

    pokemon1Item = new QGraphicsPixmapItem(QPixmap(":/pokemons/pk_sprite/1_front.png").scaled(200, 200));
    pokemon1Item->setPos(20, 70);

    pokemon2Item = new QGraphicsPixmapItem(QPixmap(":/pokemons/pk_sprite/2_front.png"));
    pokemon2Item->setPos(300, 30);

    QString healthText1 = QString::number(pokemon1->getHealth()) + "/" + fulllifePK1;

    health1 = new QGraphicsTextItem(healthText1);
    QFont promptFont("Arial", 15);
    health1->setFont(promptFont);
    health1->setPos(100, 200);

    QString healthText2 = QString::number(pokemon2->getHealth()) + "/" + fulllifePK2;

    health2 = new QGraphicsTextItem(healthText2);
    health2->setFont(promptFont);
    health2->setPos(330, 105);

}


void BattleHUD::displayOptions()
{
    scene->clear();

    scene->addItem(background);
    scene->addWidget(attackButton);
    scene->addItem(pokemon1Item);
    scene->addItem(pokemon2Item);
    scene->addItem(health1);
    scene->addItem(health2);

    scene->update();
}

void BattleHUD::attackButtonClicked()
{

}
