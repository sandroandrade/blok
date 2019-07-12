#include "isimulator.h"

ISimulator::ISimulator(QObject *parent)
    : QObject(parent)
{
}

void ISimulator::configure(QGraphicsScene *scene, IBlockBuilder *blockBuilder, ISkinFactory *skinFactory)
{
    _scene = scene;
    _blockBuilder = blockBuilder;
    _skinFactory = skinFactory;
}

ISimulator::~ISimulator()
{

}
