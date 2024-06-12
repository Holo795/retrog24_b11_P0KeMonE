#include <QTest>
#include <QKeyEvent>
#include "../App/game.h"
#include "../App/model.h"
#include "../App/gui.h"
#include "../App/player.h"


class TestCollisions : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testPlayerMovement();
    void testPlayerCollision();

private:
    Game *game;
    Model *model;
    GUI *gui;
};

void TestCollisions::initTestCase() {
    // Initialiser le modèle et l'interface graphique
    model = new Model();
    gui = new GUI(model);
    game = new Game(model, gui);

    // Afficher la fenêtre de jeu pour les tests
    game->show();
}

void TestCollisions::cleanupTestCase() {
    // Nettoyer après les tests
    delete game;
    delete gui;
    delete model;
}

void TestCollisions::testPlayerMovement() {

    QKeyEvent eventPress(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    QKeyEvent eventRelease(QEvent::KeyRelease, Qt::Key_Right, Qt::NoModifier);


    QCoreApplication::sendEvent(game, &eventPress);
    QCoreApplication::sendEvent(game, &eventRelease);


    Player *player = gui->map()->getPlayer();
    QPointF initialPos = player->pos();
    QCoreApplication::processEvents();
    QVERIFY(player->pos().x() > initialPos.x());
}

void TestCollisions::testPlayerCollision() {



    QKeyEvent eventPress(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    QKeyEvent eventRelease(QEvent::KeyRelease, Qt::Key_Up, Qt::NoModifier);


    Player *player = gui->map()->getPlayer();
    player->setPos(129, 129);


    QCoreApplication::sendEvent(game, &eventPress);
    QCoreApplication::sendEvent(game, &eventRelease);


    QPointF initialPos = player->pos();
    QCoreApplication::processEvents();
    QVERIFY(player->pos() == initialPos);
}

#include "test_collisions.moc"
