#ifndef DEFAULTBLOKSKIN_H
#define DEFAULTBLOKSKIN_H

#include "defaultblokskin_global.h"

#include <QObject>
#include "../BlokInterfaces/iplugin.h"
#include "../BlokInterfaces/iskinfactory.h"

class DEFAULTBLOKSKINSHARED_EXPORT DefaultBlokSkin
        : public QObject, public IPlugin, public ISkinFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "br.com.stone.blok.defaultblokskin")
    Q_INTERFACES (IPlugin ISkinFactory)

public:
    DefaultBlokSkin();

    bool initialize();

    IBlock *createBlock();
    IGround *createGround();
    IBackground *createBackground();
};

#endif // DEFAULTBLOKSKIN_H
