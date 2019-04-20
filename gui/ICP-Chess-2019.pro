#-------------------------------------------------
#
# Project created by QtCreator 2019-03-10T11:36:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++17

TARGET = chess
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        ../src/view/gui/main.cpp \
    ../src/view/gui/mainwindow.cpp \
    ../src/view/gui/chessboardview.cpp \
    ../src/view/gui/qchesscell.cpp \
    ../src/controller/Application.cpp \
    ../src/controller/GameInstance.cpp \
    ../src/controller/SaveSystem.cpp \
    ../src/controller/CommandSystem.cpp \
    ../src/model/SaveSerializer.cpp \
    ../src/model/Board.cpp \
    ../src/model/Rules.cpp

HEADERS += \
        ../src/view/gui/mainwindow.h \
    ../src/view/gui/chessboardview.h \
    ../src/view/gui/qchesscell.h \
    ../src/controller/Application.h \
    ../src/controller/GameInstance.h \
    ../src/controller/SaveSystem.h \
    ../src/controller/CommandSystem.h \
    ../src/model/SaveSerializer.h \
    ../src/model/Board.h \
    ../src/model/Unit.h \
    ../src/command/ICommand.h \
    ../src/command/MoveUnitCommand.h \
    ../src/common/ChessException.h \
    ../src/common/Position.h \
    ../src/common/Color.h \
    ../src/model/Rules.h

FORMS += \
        mainwindow.ui \
        chessboardview.ui

RESOURCES += resources.qrc
DESTDIR = ../bin

OBJECTS_DIR += \
    ../obj/view/gui \
    ../obj/controller \
    ../obj/model
