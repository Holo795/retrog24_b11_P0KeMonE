QT += testlib
QT += core gui widgets sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
    ../App/battle.cpp \
    ../App/battlehud.cpp \
    ../App/data.cpp \
    ../App/game.cpp \
    ../App/gameoverhud.cpp \
    ../App/gui.cpp \
    ../App/hoverbutton.cpp \
    ../App/mainhud.cpp \
    ../App/maphud.cpp \
    ../App/model.cpp \
    ../App/move.cpp \
    ../App/pktype.cpp \
    ../App/player.cpp \
    ../App/playerhud.cpp \
    ../App/pokemon.cpp \
    ../App/typeDef.cpp \
    main.cpp \
    test_collisions.cpp \
    test_database.cpp \
    test_pokemon.cpp

RESOURCES += \
    ../App/resources.qrc

HEADERS += \
    ../App/battle.h \
    ../App/battlehud.h \
    ../App/data.h \
    ../App/game.h \
    ../App/gameoverhud.h \
    ../App/gui.h \
    ../App/hoverbutton.h \
    ../App/mainhud.h \
    ../App/maphud.h \
    ../App/model.h \
    ../App/move.h \
    ../App/pktype.h \
    ../App/player.h \
    ../App/playerhud.h \
    ../App/pokemon.h \
    ../App/typeDef.h
