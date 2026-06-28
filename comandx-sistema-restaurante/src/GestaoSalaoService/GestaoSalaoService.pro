QT -= gui
TARGET = GestaoSalaoService
TEMPLATE = lib

DEFINES += GESTAOSALAOSERVICE_LIBRARY

SOURCES += \
    GestaoSalaoServiceImpl.cpp

HEADERS += \
    gestaosalaoservice_global.h \
    IGestaoSalaoService.h \
    GestaoSalaoServiceImpl.h \
    GestaoSalaoServiceFactory.h

INCLUDEPATH += $$PWD/../core
LIBS += -L$$OUT_PWD/../core -lcore
