#! [0]
TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets

include(../echoplugins.pri)

HEADERS        += echoplugin.h
SOURCES        += echoplugin.cpp
TARGET          = $$qtLibraryTarget(echoplugin)
DESTDIR         = ../../plugins
#! [0]

EXAMPLE_FILES = echoplugin.json

OTHER_FILES = $$EXAMPLE_FILES

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/echoplugin/plugins
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!
