QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battle.cpp \
    battlehud.cpp \
    data.cpp \
    game.cpp \
    gameoverhud.cpp \
    gui.cpp \
    main.cpp \
    mainhud.cpp \
    maphud.cpp \
    model.cpp \
    move.cpp \
    player.cpp \
    pokemon.cpp

HEADERS += \
    battle.h \
    battlehud.h \
    data.h \
    game.h \
    gameoverhud.h \
    gui.h \
    mainhud.h \
    maphud.h \
    model.h \
    move.h \
    player.h \
    pokemon.h \
    typeDef.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
