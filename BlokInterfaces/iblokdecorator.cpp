#include "iblokdecorator.h"

IBlokDecorator::IBlokDecorator(IBlokComponent *decorated)
    : _decorated(decorated)
{
}

IBlokDecorator::~IBlokDecorator()
{
}

void IBlokDecorator::setDecorated(IBlokComponent *decorated)
{
    _decorated = decorated;
}
