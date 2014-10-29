#-------------------------------------------------
#
# Project created by QtCreator 2014-10-25T17:34:39
#
#-------------------------------------------------

QT       += widgets

TARGET = BasicImporter
TEMPLATE = lib

DEFINES += BASICIMPORTER_LIBRARY

SOURCES += basicimporter.cpp

HEADERS += basicimporter.h\
        basicimporter_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
