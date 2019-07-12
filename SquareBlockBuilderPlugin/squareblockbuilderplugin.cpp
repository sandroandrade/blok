#include "squareblockbuilderplugin.h"

#include <QPointF>

SquareBlockBuilderPlugin::SquareBlockBuilderPlugin()
{
}

bool SquareBlockBuilderPlugin::initialize()
{
    return true;
}

QList<QPointF> SquareBlockBuilderPlugin::buildBlocks()
{
    QList<QPointF> blocks;
    int i, j;
    for (i = 0; i < 10; ++i)
        for (j = 0; j < 10; ++j)
           blocks << QPointF(-150.0f+30*i, -236.0f+30*j);
    return blocks;
}
