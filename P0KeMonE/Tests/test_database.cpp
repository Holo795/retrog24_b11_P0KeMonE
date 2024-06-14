#include <QCoreApplication>
#include <QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "../App/data.h"
#include "../App/pokemon.h"
#include "../App/move.h"

class test_database : public QObject
{
    Q_OBJECT

public:
    test_database();
    ~test_database();

private:
    Data *data;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_databaseConnection();
    void test_randomPokemon();
    void test_getMoves();
    void test_databaseClose();
};

test_database::test_database() {}

test_database::~test_database() {}

void test_database::initTestCase() {
    data = new Data();
}

void test_database::cleanupTestCase() {
    delete data;
}

void test_database::test_databaseConnection() {
    QVERIFY(data->getDatabase().open());
}

void test_database::test_randomPokemon() {
    Pokemon* pokemon = data->randompokemon();
    QVERIFY(pokemon != nullptr);
    QVERIFY(!pokemon->getItsName().empty());
    QVERIFY(pokemon->getHealth() > 0);
    delete pokemon;
}

void test_database::test_getMoves() {
    QList<Move*> moves = data->getMoves(1);  // Assuming there is a Pokémon with ID 1
    QVERIFY(!moves.isEmpty());
    for (Move* move : moves) {
        QVERIFY(!move->getItsName().empty());
        QVERIFY(move->getItsPower() >= 0);
        QVERIFY(move->getItsAccuracy() >= 0 && move->getItsAccuracy() <= 100);
        delete move;
    }
}

void test_database::test_databaseClose() {
    data->getDatabase().close();
    QVERIFY(!data->getDatabase().isOpen());
}

#include "test_database.moc"
