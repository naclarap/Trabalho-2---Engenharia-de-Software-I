QT -= gui
TARGET = GestaoComandasService
TEMPLATE = lib

DEFINES += GESTAOCOMANDASSERVICE_LIBRARY

SOURCES += \
    GestaoComandasServiceImpl.cpp

HEADERS += \
    Gestaocomandasservice_global.h \
    IGestaoComandasService.h \
    GestaoComandasServiceImpl.h \
    GestaoComandasServiceFactory.h

INCLUDEPATH += $$PWD/../core $$PWD/../GestaoSalaoService $$PWD/../CardapioDigitalService
LIBS += -L$$OUT_PWD/../core -lcore
LIBS += -L$$OUT_PWD/../GestaoSalaoService -lGestaoSalaoService
LIBS += -L$$OUT_PWD/../CardapioDigitalService -lCardapioDigitalService
