#ifndef SWORDDECORATORPLUGIN_H
#define SWORDDECORATORPLUGIN_H

#include "sworddecoratorplugin_global.h"

#include <QObject>
#include "../BlokInterfaces/iplugin.h"
#include "../BlokInterfaces/iblokdecorator.h"

class SWORDDECORATORPLUGINSHARED_EXPORT SwordDecoratorPlugin
        : public QObject, public IPlugin, public IBlokDecorator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "br.com.stone.blok.sworddecoratorplugin")
    Q_INTERFACES(IPlugin IBlokDecorator)

public:
    SwordDecoratorPlugin();

    bool initialize() Q_DECL_OVERRIDE;
    QGraphicsItem *createPlayer() Q_DECL_OVERRIDE;
};

#endif // SWORDDECORATORPLUGIN_H
