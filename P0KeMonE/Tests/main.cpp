#include <QCoreApplication>
#include <QtTest>
#include "test_database.cpp"

int main(int argc, char *argv[])
{

    QCoreApplication app(argc, argv);

    int status = 0;

    {
        test_database tc1;
        status |= QTest::qExec(&tc1, argc, argv);
    }

    return 0;
}

