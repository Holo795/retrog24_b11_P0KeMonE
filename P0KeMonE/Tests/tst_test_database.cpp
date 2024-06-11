#include <QCoreApplication>
#include <QtTest>

#include "../App/data.h"

// add necessary includes here

class test_database : public QObject
{
    Q_OBJECT

public:
    test_database();
    ~test_database();

private slots:
    void test_case1();
};

test_database::test_database() {

}

test_database::~test_database() {}

void test_database::test_case1() {}

QTEST_MAIN(test_database)

#include "tst_test_database.moc"
