QT += quick quickcontrols2

HEADERS    = echointerface.h
SOURCES    = main.cpp
RESOURCES += qml.qrc

TARGET     = echoplugin
QMAKE_PROJECT_NAME = echopluginwindow
win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/
    CONFIG(release, release|debug):DESTDIR = ../release/
} else {
    DESTDIR    = ../
}

HEADERS    += pluginmanager.h
SOURCES    += pluginmanager.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/echoplugin
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!
