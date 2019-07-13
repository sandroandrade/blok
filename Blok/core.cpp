#include "core.h"

#include "uicontroller.h"
#include "plugincontroller.h"

Core::Core(QObject *parent) : ICore(parent),
    _pluginController(new PluginController(this)),
    _uiController(new UIController(this))
{
}

Core::~Core()
{
}

bool Core::initialize()
{
    if (_instance)
        return false;
    _instance = new Core;
    _instance->pluginController()->initialize();
    _instance->uiController()->initialize();
    return true;
}

IPluginController *Core::pluginController()
{
    return _pluginController;
}

IUIController *Core::uiController()
{
    return _uiController;
}
