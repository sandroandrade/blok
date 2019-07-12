#ifndef IPLUGINCONTROLLER_H
#define IPLUGINCONTROLLER_H

#include "blokinterfaces_global.h"

#include <QObject>
#include <QHash>

class IPlugin;

class BLOKINTERFACESSHARED_EXPORT IPluginController : public QObject
{
    Q_OBJECT
public:
    explicit IPluginController(QObject *parent = nullptr);
    virtual bool initialize() = 0;
    template<typename T = IPlugin>
    QHash<QString, T *> loadedPlugins() const {
        QHash<QString, T *> loadedPluginsByType;
        T *pluginOfType = nullptr;
        for (const auto &fileName : _loadedPlugins.keys())
            if ((pluginOfType = dynamic_cast<T *>(_loadedPlugins[fileName])))
                loadedPluginsByType[fileName] = pluginOfType;
        return loadedPluginsByType;
    }

protected:
    QHash<QString, IPlugin *> _loadedPlugins;
};

#endif // IPLUGINCONTROLLER_H
