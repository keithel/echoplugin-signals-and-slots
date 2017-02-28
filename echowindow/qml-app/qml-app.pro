QT += quick quickcontrols2

include(../echowindow.pri)

SOURCES   += main.cpp
RESOURCES += qml.qrc

TARGET     = echoplugin-qml
QMAKE_PROJECT_NAME = echoplugin-qml

win32 {
    CONFIG(debug, release|debug):DESTDIR = ../../debug/
    CONFIG(release, release|debug):DESTDIR = ../../release/
} else {
    DESTDIR    = ../../
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/echoplugin
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!
