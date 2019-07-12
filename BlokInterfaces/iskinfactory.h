#ifndef ISKINFACTORY_H
#define ISKINFACTORY_H

#include "blokinterfaces_global.h"

#include <QtPlugin>

class IBlock;
class IGround;
class IBackground;

class BLOKINTERFACESSHARED_EXPORT ISkinFactory
{
public:
    virtual ~ISkinFactory();

    virtual IBlock *createBlock() = 0;
    virtual IGround *createGround() = 0;
    virtual IBackground *createBackground() = 0;
};

Q_DECLARE_INTERFACE(ISkinFactory, "br.com.stone.blok.iskinfactory")

#endif // ISKINFACTORY_H
