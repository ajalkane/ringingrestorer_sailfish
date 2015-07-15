DEFINES += RR_JOLLA_STORE_CRIPPLED
# If RR_TESTING enabled then restoration happens in seconds instead of minutes (ie. 60 times faster than what is selected)
# DEFINES += RR_TESTING

# The name of your application
TARGET = harbour-ringingrestorer

CONFIG += sailfishapp

# app portion
QT += dbus
# daemon portion
QT += quick qml dbus
# Copied from: https://github.com/sailfishos-patches/partnerspacemanager/blob/master/README.md
QT += gui-private
QMAKE_CXXFLAGS += -std=c++0x
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
# End of daemon portion

SOURCES += src/maininit.cpp \
    src/main.cpp \
    src/app/controlclient.cpp \
    src/app/qmlbackend.cpp \
    src/app/appmaininit.cpp \
    src/daemon/logic/profilechangewatcher.cpp \
    src/daemon/interface/controlinterface.cpp \
    src/daemon/qmldaemonbackend.cpp \
    src/daemon/profileclient.cpp \
    src/daemon/preferences.cpp \
    src/daemon/configuration.cpp \
    src/daemon/systemalignedtimer.cpp \
    src/daemon/daemonmaininit.cpp

HEADERS += src/maininit.h \
    src/app/controlclient.h \
    src/app/qmlbackend.h \
    src/app/appmaininit.h \
    src/daemon/logic/profilechangewatcher.h \
    src/daemon/interface/controlinterface.h \
    src/daemon/profileclient.h \
    src/daemon/preferences.h \
    src/daemon/configuration.h \
    src/daemon/systemalignedtimer.h \
    src/daemon/qmldaemonbackend.h \
    src/daemon/daemonmaininit.h

contains(DEFINES, RR_JOLLA_STORE_CRIPPLED) {
    SOURCES += src/app/processcontrol.cpp
    HEADERS += src/app/processcontrol.h
}

OTHER_FILES += qml/app/harbour-ringingrestorer.qml \
    qml/app/cover/CoverPage.qml \
    qml/app/pages/FirstPage.qml \
    qml/app/pages/AboutPage.qml \
    qml/daemon/main.qml \
    qml/daemon/cover/CoverPage.qml \
    qml/daemon/pages/FirstPage.qml \
    qml/daemon/pages/RestoreRingingDialog.qml \
    translations/*.ts \
    harbour-ringingrestorer.desktop

# libiphb sources
SOURCES += src/daemon/libiphb/src/libiphb.c
HEADERS += src/daemon/libiphb/src/libiphb.h src/daemon/libiphb/src/iphb_internal.h
LIBS += -lrt

# nemo-keepalive's heartbeat sources (required by heartbeat)
SOURCES += src/daemon/nemo-keepalive/lib/heartbeat.cpp
HEADERS += src/daemon/nemo-keepalive/lib/heartbeat.h
INCLUDEPATH += $$PWD/src/daemon/include

# BackgroundActivity
system(qdbusxml2cpp -p src/daemon/generated/mceiface/mceiface.h:src/daemon/generated/mceiface/mceiface.cpp src/daemon/nemo-keepalive/lib/mceiface.xml)

# End of daemon portion

system(rm -rf rpm/*)
system(mkdir -p rpm)

!contains(DEFINES, RR_JOLLA_STORE_CRIPPLED) {
    system(cp rpm.openrepos/* rpm/)
} else {
    system(cp rpm.jollastore/* rpm/)
}

OTHER_FILES += \
    rpm/harbour-ringingrestorer.yaml \
    rpm/harbour-ringingrestorer.changes \
    rpm/harbour-ringingrestorer.spec

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/HelloWorld-de.ts

#TEMPLATE = subdirs

#include("harbour-ringingrestorer-defines.pri")

#SUBDIRS += app
#SUBDIRS += daemon

#system(rm -rf rpm/*)
#system(mkdir -p rpm)

#!contains(DEFINES, RR_JOLLA_STORE_CRIPPLED) {
#    system(cp rpm.openrepos/* rpm/)
#} else {
#    system(cp rpm.jollastore/* rpm/)
#}

#OTHER_FILES += \
#    rpm/harbour-ringingrestorer.yaml \
#    rpm/harbour-ringingrestorer.changes \
#    rpm/harbour-ringingrestorer.spec
