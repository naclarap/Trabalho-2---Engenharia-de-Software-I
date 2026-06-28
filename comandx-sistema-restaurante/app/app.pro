QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComandXApp
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

# Path para encontrar os headers de todas as libs
INCLUDEPATH += $$PWD/../libs/core
INCLUDEPATH += $$PWD/../libs/ControleAcessoService
INCLUDEPATH += $$PWD/../libs/GestaoSalaoService
INCLUDEPATH += $$PWD/../libs/CardapioDigitalService
INCLUDEPATH += $$PWD/../libs/GestaoComandasService

# Path para encontrar os arquivos .dll/.so e linkar com eles
LIBS += -L$$OUT_PWD/../libs/core -lcore
LIBS += -L$$OUT_PWD/../libs/ControleAcessoService -lControleAcessoService
LIBS += -L$$OUT_PWD/../libs/GestaoSalaoService -lGestaoSalaoService
LIBS += -L$$OUT_PWD/../libs/CardapioDigitalService -lCardapioDigitalService
LIBS += -L$$OUT_PWD/../libs/GestaoComandasService -lGestaoComandasService
