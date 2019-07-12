#include "icore.h"

ICore *ICore::_instance = nullptr;

ICore::ICore(QObject *parent) : QObject(parent)
{
}

ICore::~ICore()
{

}

ICore *ICore::instance()
{
    Q_ASSERT(_instance);
    return _instance;
}
