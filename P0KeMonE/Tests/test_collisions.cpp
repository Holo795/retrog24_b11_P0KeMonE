#include <QTest>
#include <QKeyEvent>
#include "../App/game.h"
#include "../App/model.h"
#include "../App/gui.h"
#include "../App/player.h"


class test_collisions : public QObject {
    Q_OBJECT

public:
    test_collisions();
    ~test_collisions();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testPlayerCollisionLeft();

private:
    Game *game;
    Model *model;
    GUI *gui;
    Player *player;
};

test_collisions::test_collisions() {}

test_collisions::~test_collisions() {}

void test_collisions::initTestCase() {
    // Initialiser le modèle et l'interface graphique
    model = new Model();
    gui = new GUI(model);
    game = new Game(model, gui);
    player = new Player();
    player->setPos(129, 193);
}

void test_collisions::cleanupTestCase() {
    // Nettoyer après les tests
    delete game;
    delete gui;
    delete model;
    delete player;
}


void test_collisions::testPlayerCollisionLeft() {
    qDebug() << "**********testPlayerCollisionLeft start**********";
    QPointF initialPos = player->pos();
    qDebug() << "Initial position:" << initialPos;

    // Simuler l'appui sur la flèche vers le haut
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    player->keyPressEvent(&event);

    // Vérifier que le joueur n'a pas bougé (collision)
    qDebug() << "Player position after key press:" << player->pos();
    QVERIFY(player->pos() == initialPos);

    qDebug() << "**********testPlayerCollisionLeft end**********";
}


#include "test_collisions.moc"
