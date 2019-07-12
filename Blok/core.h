#ifndef CORE_H
#define CORE_H

#include "../BlokInterfaces/icore.h"

class Core : public ICore
{
public:
    ~Core();

    static bool initialize();
    IPluginController *pluginController();
    IUIController *uiController();

private:
    Core(QObject *parent = nullptr);
    IPluginController *_pluginController;
    IUIController *_uiController;
};

#endif // CORE_H
