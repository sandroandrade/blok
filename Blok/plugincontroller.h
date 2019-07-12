#ifndef PLUGINCONTROLLER_H
#define PLUGINCONTROLLER_H

#include "../BlokInterfaces/iplugincontroller.h"

class PluginController : public IPluginController
{
public:
    PluginController(QObject *parent = nullptr);

    // IPluginController interface
public:
    bool initialize();
};

#endif // PLUGINCONTROLLER_H
