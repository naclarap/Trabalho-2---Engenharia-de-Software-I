QT -= gui
TARGET = CardapioDigitalService
TEMPLATE = lib
DEFINES += CARDIAPIODIGITALSERVICE_LIBRARY
SOURCES += CardapioDigitalServiceImpl.cpp
# A linha duplicada foi removida daqui:
HEADERS += cardapiodigitalservice_global.h ICardapioDigitalService.h CardapioDigitalServiceImpl.h CardapioDigitalServiceFactory.h
INCLUDEPATH += $$PWD/../core
LIBS += -L$$OUT_PWD/../core -lcore
