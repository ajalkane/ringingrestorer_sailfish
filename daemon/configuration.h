#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QList>
#include <QSettings>

#include "preferences.h"

class Configuration
{
public:
    Configuration();

    static void writePreferences(const Preferences &preferences);
    static void readPreferences(Preferences &preferences);

};

#endif // CONFIGURATION_H
