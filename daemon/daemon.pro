TARGET = harbour-ringingrestorerd

# CONFIG += sailfishapp

QT += quick qml dbus

# Copied from: https://github.com/sailfishos-patches/partnerspacemanager/blob/master/README.md
QT += gui-private

QMAKE_CXXFLAGS += -std=c++0x

DEFINES += APP_VERSION=\\\"$$VERSION\\\"
# If defined, restoring happens in seconds instead of in minutes
# DEFINES += RR_TESTING

SOURCES += main.cpp \
    logic/profilechangewatcher.cpp \
    interface/controlinterface.cpp \
    qmlbackend.cpp \
    profileclient.cpp \
    preferences.cpp \
    configuration.cpp \
    systemalignedtimer.cpp

HEADERS += \
    logic/profilechangewatcher.h \
    interface/controlinterface.h \
    qmlbackend.h \
    profileclient.h \
    preferences.h \
    configuration.h \
    systemalignedtimer.h

OTHER_FILES += \
    qml/main.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml

# libiphb sources
SOURCES += libiphb/src/libiphb.c
HEADERS += libiphb/src/libiphb.h libiphb/src/iphb_internal.h
LIBS += -lrt

# nemo-keepalive's heartbeat sources (required by heartbeat)
SOURCES += nemo-keepalive/lib/heartbeat.cpp
HEADERS += nemo-keepalive/lib/heartbeat.h
INCLUDEPATH += $$PWD/include

# BackgroundActivity
system(qdbusxml2cpp -p generated/mceiface/mceiface.h:generated/mceiface/mceiface.cpp nemo-keepalive/lib/mceiface.xml)
# system(qdbusxml2cpp -p nemo-keepalive/lib/mceiface.h:nemo-keepalive/lib/mceiface.cpp nemo-keepalive/lib/mceiface.xml)
# INCLUDEPATH += $$PWD/include
#SOURCES += nemo-keepalive/lib/backgroundactivity.cpp \
#           nemo-keepalive/lib/backgroundactivity_p.cpp \
#           generated/mceiface/mceiface.cpp
#HEADERS += nemo-keepalive/lib/backgroundactivity.h \
#           nemo-keepalive/lib/backgroundactivity_p.h \
#           generated/mceiface/mceiface.h

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

