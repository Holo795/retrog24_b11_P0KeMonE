QT       += core gui

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
    main.cpp \
    gui.cpp \
    model.cpp \
    move.cpp \
    player.cpp \
    pokemon.cpp \
    screen.cpp

HEADERS += \
    battle.h \
    battlehud.h \
    data.h \
    game.h \
    gui.h \
    model.h \
    move.h \
    player.h \
    pokemon.h \
    screen.h \
    typeDef.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
