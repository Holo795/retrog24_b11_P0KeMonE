#include <QtTest>
#include "../App/pokemon.h"


class test_pokemon : public QObject
{
    Q_OBJECT

public:
    test_pokemon();
    ~test_pokemon();

private:
    Pokemon *pokemon;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_pokemonName();
    void test_pokemonDead();
    void test_pokemonTakeDamage();
};

test_pokemon::test_pokemon() {}

test_pokemon::~test_pokemon() {}

void test_pokemon::initTestCase() {
    pokemon = new Pokemon(1, "Pikachu", PKTYPE::Electric, 100, 90, 55, 50, 40, 50, 50);
}


void test_pokemon::cleanupTestCase() {
    delete pokemon;
}

void test_pokemon::test_pokemonName() {
    QVERIFY(pokemon->getItsName() == "Pikachu");
}

void test_pokemon::test_pokemonDead() {
    pokemon->setItsHealth(0);
    QVERIFY(pokemon->isDead(*pokemon) == true);
}

void test_pokemon::test_pokemonTakeDamage() {
    pokemon->setItsHealth(100);
    pokemon->takeDamage(10);
    QVERIFY(pokemon->getHealth() == 90);
}



#include "test_pokemon.moc"
