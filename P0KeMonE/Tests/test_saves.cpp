#include <QCoreApplication>
#include <QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "../App/data.h"
#include "../App/player.h"
#include "../App/savemanager.h"

class test_saves : public QObject
{
    Q_OBJECT

public:
    test_saves();
    ~test_saves();

private:
    Data *data;
    Player *player;
    SaveManager *saveManager;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_saveGame();

    void test_savesConnection();
    void test_savesClose();

};

test_saves::test_saves() {}

test_saves::~test_saves() {}

void test_saves::initTestCase() {
    data = new Data();
    player = new Player();
    vector<Pokemon*>teamTest;
    teamTest.push_back(new Pokemon(15, "Beedrill", PKTYPE::Electric, 100, 90, 55, 50, 40, 50, 1));
    teamTest.push_back(new Pokemon(46, "Paras", PKTYPE::Ground, 100, 90, 55, 50, 40, 50, 1));
    player->setTeam(teamTest);
    player->setItsLevel(3.0);
    player->setPos(150,250);
    saveManager = new SaveManager(data, player);
    saveManager->saveGame();
}

void test_saves::cleanupTestCase() {
    delete data;
    delete player;
    delete saveManager;
}

void test_saves::test_saveGame(){
    saveData save = saveManager->getSave();
    QVERIFY(save.player_lvl == 3);
    QVERIFY(save.player_x == 150);
    QVERIFY(save.player_y == 250);
    QVERIFY(save.team.size() == 2);
    QVERIFY(save.team[0]->getItsName() == "Beedrill");
    QVERIFY(save.team[1]->getItsName() == "Paras");
}

void test_saves::test_savesConnection() {
    QVERIFY(data->getDatabase().open());
}

void test_saves::test_savesClose() {
    data->getDatabase().close();
    QVERIFY(!data->getDatabase().isOpen());
}

#include "test_saves.moc"
