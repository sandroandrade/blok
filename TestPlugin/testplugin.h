#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include "../BlokInterfaces/iplugin.h"

#include "testplugin_global.h"

#include <QObject>

class TESTPLUGINSHARED_EXPORT TestPlugin : public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "br.com.stone.blok.testplugin")
    Q_INTERFACES(IPlugin)

public:
    TestPlugin();

    bool initialize();
};

#endif // TESTPLUGIN_H
