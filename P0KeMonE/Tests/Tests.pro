QT += testlib
QT += core gui widgets sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_test_database.cpp \
    ../App/data.cpp \
    ../App/model.cpp \
    ../App/move.cpp \
    ../App/pktype.cpp \
    ../App/pokemon.cpp \
    ../App/typeDef.cpp

RESOURCES += \
    ../App/resources.qrc

HEADERS += \
    ../App/data.h \
    ../App/model.h \
    ../App/move.h \
    ../App/pktype.h \
    ../App/pokemon.h \
    ../App/typeDef.h
