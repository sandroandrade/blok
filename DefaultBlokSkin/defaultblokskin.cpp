#include "defaultblokskin.h"

#include "defaultblock.h"
#include "defaultground.h"
#include "defaultbackground.h"

DefaultBlokSkin::DefaultBlokSkin()
{
}

bool DefaultBlokSkin::initialize()
{
    return true;
}

IBlock *DefaultBlokSkin::createBlock()
{
    return new DefaultBlock;
}

IGround *DefaultBlokSkin::createGround()
{
    return new DefaultGround;
}

IBackground *DefaultBlokSkin::createBackground()
{
    return new DefaultBackground;
}
