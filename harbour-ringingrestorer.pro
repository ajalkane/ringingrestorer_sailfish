# The name of your application
TARGET = harbour-ringingrestorer
TEMPLATE = subdirs

SUBDIRS += app
SUBDIRS += daemon

OTHER_FILES += \
    rpm/harbour-ringingrestorer.yaml \
    rpm/harbour-ringingrestorer.changes \
    rpm/harbour-ringingrestorer.spec

