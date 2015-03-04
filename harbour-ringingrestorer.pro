# The name of your application
TARGET = harbour-ringingrestorer
TEMPLATE = subdirs

include("harbour-ringingrestorer-defines.pri")

SUBDIRS += app
SUBDIRS += daemon

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
