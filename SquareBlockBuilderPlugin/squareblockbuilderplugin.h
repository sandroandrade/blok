#ifndef SQUAREBLOCKBUILDERPLUGIN_H
#define SQUAREBLOCKBUILDERPLUGIN_H

#include <QObject>
#include "../BlokInterfaces/iplugin.h"
#include "../BlokInterfaces/iblockbuilder.h"

#include "squareblockbuilderplugin_global.h"

class SQUAREBLOCKBUILDERPLUGINSHARED_EXPORT SquareBlockBuilderPlugin
        : public QObject, public IPlugin, public IBlockBuilder
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "br.com.stone.blok.squareblockbuilderplugin")
    Q_INTERFACES(IPlugin IBlockBuilder)

public:
    SquareBlockBuilderPlugin();
    bool initialize();
    QList<QPointF> buildBlocks();
};

#endif // SQUAREBLOCKBUILDERPLUGIN_H
