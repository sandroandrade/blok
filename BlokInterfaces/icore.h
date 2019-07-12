#ifndef ICORE_H
#define ICORE_H

#include "blokinterfaces_global.h"

#include <QObject>

class IPluginController;
class IUIController;

class BLOKINTERFACESSHARED_EXPORT ICore : public QObject
{
public:
    virtual ~ICore();
    static ICore *instance();
    virtual IPluginController *pluginController()= 0;
    virtual IUIController *uiController() = 0;

protected:
    ICore(QObject *parent = nullptr);
    static ICore *_instance;
};

#endif // ICORE_H
