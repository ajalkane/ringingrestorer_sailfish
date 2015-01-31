TARGET = harbour-ringingrestorerd

# CONFIG += sailfishapp

QT += quick qml dbus

# Copied from: https://github.com/sailfishos-patches/partnerspacemanager/blob/master/README.md
QT += gui-private

QMAKE_CXXFLAGS += -std=c++0x

DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += RR_TESTING

SOURCES += main.cpp \
    logic/profilechangewatcher.cpp \
    interface/controlinterface.cpp \
    qmlbackend.cpp \
    profileclient.cpp \
    preferences.cpp \
    configuration.cpp

HEADERS += \
    logic/profilechangewatcher.h \
    interface/controlinterface.h \
    qmlbackend.h \
    profileclient.h \
    preferences.h \
    configuration.h

OTHER_FILES += \
    qml/main.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml

# libiphb sources
SOURCES += libiphb/src/libiphb.c
HEADERS += libiphb/src/libiphb.h libiphb/src/iphb_internal.h
# PKGCONFIG += libiphb

# INSTALLS += target ringingrestorerd qml # daemon_qmlfiles

# Workaround for daemon's qml files, thanks to Coderus for giving hints about the problem. Basically copied the
# relevant parts from https://github.com/sailfish-sdk/libsailfishapp/blob/master/data/sailfishapp.prf
target.path = /usr/bin

qml.files = qml
qml.path = /usr/share/$${TARGET}

INSTALLS += qml target ringingrestorerd

CONFIG += link_pkgconfig
PKGCONFIG += sailfishapp
INCLUDEPATH += /usr/include/sailfishapp

# End of workaround

ringingrestorerd.files = $${TARGET}.service
ringingrestorerd.path = /usr/lib/systemd/user

