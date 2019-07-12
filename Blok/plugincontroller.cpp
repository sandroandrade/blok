#include "plugincontroller.h"

#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

#include "../BlokInterfaces/iplugin.h"

PluginController::PluginController(QObject *parent)
    : IPluginController(parent)
{
}

bool PluginController::initialize()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    for (const auto &fileName : pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        IPlugin *plugin = qobject_cast<IPlugin *>(loader.instance());
        if (plugin) {
            if (plugin->initialize())
                _loadedPlugins[fileName] = plugin;
        }
        else {
            qDebug() << "It's not an IPlugin or" << loader.errorString();
        }
    }
    return true;
}
