#ifndef IBLOCKBUILDER_H
#define IBLOCKBUILDER_H

#include "blokinterfaces_global.h"

#include <QtPlugin>

class BLOKINTERFACESSHARED_EXPORT IBlockBuilder
{
public:
    virtual ~IBlockBuilder();

    virtual QList<QPointF> buildBlocks() = 0;
};

Q_DECLARE_INTERFACE(IBlockBuilder, "br.com.stone.blok.iblockbuilder")

#endif // IBLOCKBUILDER_H
