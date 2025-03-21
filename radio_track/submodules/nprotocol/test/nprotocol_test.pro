QT += core
QT -= gui

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

TARGET = test
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

TEMPLATE = app

LIBS += -lboost_system -lboost_unit_test_framework

INCLUDEPATH += ../

CONFIG(debug, debug|release) {
   DESTDIR = $$BUILD_DIR_DEBUG#/debug
} else {
   DESTDIR = $$BUILD_DIR_RELEASE#/release
}


SOURCES += \
    test.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    ../serializable_pp.hpp \
    ../serializer_cxx17.hpp \
    ../serializer.hpp
