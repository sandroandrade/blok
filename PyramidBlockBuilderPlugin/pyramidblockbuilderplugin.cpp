#include "pyramidblockbuilderplugin.h"

#include <QPointF>

PyramidBlockBuilderPlugin::PyramidBlockBuilderPlugin()
{
}

bool PyramidBlockBuilderPlugin::initialize()
{
    return true;
}

QList<QPointF> PyramidBlockBuilderPlugin::buildBlocks()
{
    QList<QPointF> blocks;
    int i, j;
    for (i = 0; i < 10; ++i)
        for (j = 0; j < 11 - i; ++j)
           blocks << QPointF(-150.0f+15*i+30*j, -236.0f+30*i);
    return blocks;
}
