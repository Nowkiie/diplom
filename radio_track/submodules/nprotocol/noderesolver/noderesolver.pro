TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

LIBS += -lboost_system -lpthread

INCLUDEPATH += ../

SOURCES += \
    noderesolver.cpp


QMAKE_CXXFLAGS += -fvisibility=hidden
QMAKE_CXXFLAGS += -fvisibility-inlines-hidden

CONFIG(release, debug|release) {
    QMAKE_LFLAGS += -Wl,--strip-all
}

