QT += testlib
QT += core gui widgets sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
    ../App/data.cpp \
    ../App/model.cpp \
    ../App/move.cpp \
    ../App/pktype.cpp \
    ../App/pokemon.cpp \
    ../App/typeDef.cpp \
    main.cpp \
    test_database.cpp

RESOURCES += \
    ../App/resources.qrc

HEADERS += \
    ../App/data.h \
    ../App/model.h \
    ../App/move.h \
    ../App/pktype.h \
    ../App/pokemon.h \
    ../App/typeDef.h
