#include <QtTest>
#include "../App/player.h"
#include "../App/pokemon.h"

class test_player : public QObject
{
    Q_OBJECT

public:
    test_player();
    ~test_player();

private:
    Player *player;
    Pokemon *pokemon1;
    Pokemon *pokemon2;
private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_moveUp();
    void test_moveLeft();
    void test_moveRight();
    void test_moveDown();
    void test_addPokemon();
};

test_player::test_player() {}

test_player::~test_player() {}

void test_player::initTestCase() {
    player = new Player();
    player->setPos(225, 353);
}


void test_player::cleanupTestCase() {
    delete player;
}

void test_player::test_moveUp() {
    // Obtenir la position initiale du joueur
    QPointF initialPos = player->pos();

    // Simuler l'appui sur la flèche vers le haut
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    player->keyPressEvent(&event);

    // Vérification si le joueur a bien bougé vers le haut
    QVERIFY(player->pos().y() <= initialPos.y()); // Vérifie que la position en y a diminué ou est restée inchangée
}

void test_player::test_moveLeft() {
    // Obtenir la position initiale du joueur
    QPointF initialPos = player->pos();

    // Simuler l'appui sur la flèche vers la gauche
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    player->keyPressEvent(&event);

    // Vérification si le joueur a bien bougé vers la gauche
    QVERIFY(player->pos().x() <= initialPos.x()); // Vérifie que la position en x a diminué ou est restée inchangée
}

void test_player::test_moveRight() {
    // Obtenir la position initiale du joueur
    QPointF initialPos = player->pos();

    // Simuler l'appui sur la flèche vers la droite
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    player->keyPressEvent(&event);

    // Vérification si le joueur a bien bougé vers la droite
    QVERIFY(player->pos().x() >= initialPos.x()); // Vérifie que la position en x a augmenté ou est restée inchangée
}

void test_player::test_moveDown() {
    // Obtenir la position initiale du joueur
    QPointF initialPos = player->pos();

    // Simuler l'appui sur la flèche vers le bas
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
    player->keyPressEvent(&event);

    // Vérification si le joueur a bien bougé vers le bas
    QVERIFY(player->pos().y() >= initialPos.y()); // Vérifie que la position en y a augmenté ou est restée inchangée
}


void test_player::test_addPokemon() {
    pokemon1 = new Pokemon(1, "Pikachu", PKTYPE::Electric, 100, 90, 55, 40, 50, 50, 50);
    pokemon2 = new Pokemon(2, "Raichu", PKTYPE::Electric, 100, 90, 55, 40, 50, 50, 50);
    player->addPokemon(pokemon1);
    player->addPokemon(pokemon2);

    std::vector<Pokemon*> expectedTeam = {pokemon1, pokemon2};

    QCOMPARE(player->getTeam(), expectedTeam);
}


#include "test_player.moc"
