QT += testlib
CONFIG += testcase console

TARGET = tst_comandx
TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

# Adicione aqui todos os ficheiros .cpp dos seus testes
SOURCES += \
    tst_autenticacao.cpp \
    tst_cardapio.cpp \
    tst_gestaocomandas.cpp \
    tst_gestaosalao.cpp \



# Path para encontrar os headers de todas as suas bibliotecas
INCLUDEPATH += $$PWD/../libs/core
INCLUDEPATH += $$PWD/../libs/ControleAcessoService
INCLUDEPATH += $$PWD/../libs/GestaoSalaoService
INCLUDEPATH += $$PWD/../libs/CardapioDigitalService
INCLUDEPATH += $$PWD/../libs/GestaoComandasService

# Path para linkar com os ficheiros .dll/.so das suas bibliotecas
LIBS += -L$$OUT_PWD/../libs/core -lcore
LIBS += -L$$OUT_PWD/../libs/ControleAcessoService -lControleAcessoService
LIBS += -L$$OUT_PWD/../libs/GestaoSalaoService -lGestaoSalaoService
LIBS += -L$$OUT_PWD/../libs/CardapioDigitalService -lCardapioDigitalService
LIBS += -L$$OUT_PWD/../libs/GestaoComandasService -lGestaoComandasService
