TEMPLATE = lib
TARGET = map-lib
CONFIG += c++17 static
QT += core gui svg widgets sql xml
QMAKE_CXXFLAGS += -std=c++17
DESTDIR = $$PWD/../lib


INCLUDEPATH += \
    ../submodules/BaseMap \
    ../submodules/nprotocol

include(map-lib.pri)
