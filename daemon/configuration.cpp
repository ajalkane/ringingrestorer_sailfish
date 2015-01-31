#include <QSettings>
#include <QUuid>

#include "configuration.h"

Configuration::Configuration()
{
}

void
Configuration::writePreferences(const Preferences &p) {
    qDebug("Configuration::writePreferences()");

    // IMPROVE constants.h
    // So wrong by the API specifications, but so right by the end results (no, I don't like doing it this way)
    QSettings s("RingingRestorer", "preferences");
    s.clear();
    s.setValue("isActive", p.isActive);
}

void
Configuration::readPreferences(Preferences &p) {
    // IMPROVE constants.h
    // So wrong by the API specifications, but so right by the end results (no, I don't like doing it this way)
    QSettings s("RingingRestorer", "preferences");
    p.isActive = s.value("isActive", true).toBool();
}
