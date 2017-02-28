#! [0]
TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets

include(../echoplugins.pri)

HEADERS        += rot13-plugin.h
SOURCES        += rot13-plugin.cpp
TARGET          = $$qtLibraryTarget(rot13-plugin)
DESTDIR         = ../../plugins
#! [0]

EXAMPLE_FILES = rot13-plugin.json

OTHER_FILES = $$EXAMPLE_FILES

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/echoplugin/plugins
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!
