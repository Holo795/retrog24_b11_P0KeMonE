QT       += core gui
QT       += sql
QT += multimedia


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
    hoverbutton.cpp \
    main.cpp \
    mainhud.cpp \
    maphud.cpp \
    model.cpp \
    move.cpp \
    player.cpp \
    playerhud.cpp \
    pokemon.cpp \
    savemanager.cpp \
    soundmanager.cpp \
    typeDef.cpp

HEADERS += \
    battle.h \
    battlehud.h \
    data.h \
    game.h \
    gameoverhud.h \
    gui.h \
    hoverbutton.h \
    include/json.hpp \
    mainhud.h \
    maphud.h \
    model.h \
    move.h \
    player.h \
    playerhud.h \
    pokemon.h \
    savemanager.h \
    soundmanager.h \
    typeDef.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
