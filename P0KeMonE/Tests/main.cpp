#include <QGuiApplication>
#include <QtTest>
#include "test_database.cpp"
#include "test_pokemon.cpp"
#include "test_player.cpp"
#include "test_saves.cpp"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    int status = 0;

    {
        test_database tc1;
        status |= QTest::qExec(&tc1, argc, argv);
    }

    {
        test_pokemon tc2;
        status |= QTest::qExec(&tc2, argc, argv);
    }

    {
        test_player tc3;
        status |= QTest::qExec(&tc3, argc, argv);
    }

    {
        test_saves tc4;
        status |= QTest::qExec(&tc4, argc, argv);
    }


    return 0;
}

