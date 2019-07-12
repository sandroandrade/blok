#ifndef PYRAMIDBLOCKBUILDERPLUGIN_H
#define PYRAMIDBLOCKBUILDERPLUGIN_H

#include <QObject>
#include "../BlokInterfaces/iplugin.h"
#include "../BlokInterfaces/iblockbuilder.h"

#include "pyramidblockbuilderplugin_global.h"

class PYRAMIDBLOCKBUILDERPLUGINSHARED_EXPORT PyramidBlockBuilderPlugin
        : public QObject, public IPlugin, public IBlockBuilder
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "br.com.stone.blok.pyramidblockbuilderplugin")
    Q_INTERFACES(IPlugin IBlockBuilder)

public:
    PyramidBlockBuilderPlugin();
    bool initialize();
    QList<QPointF> buildBlocks();
};

#endif // PYRAMIDBLOCKBUILDERPLUGIN_H
