#include "blokremovalcommand.h"

#include "../BlokInterfaces/isimulator.h"
#include <QGraphicsView>
#include <QMessageBox>

BlokRemovalCommand::BlokRemovalCommand(ISimulator *simulator,
                                       QGraphicsView *graphicsView,
                                       QPointF removedBlockPosition,
                                       QList<QPointF> allBlocksPosition,
                                       QPointF playerPosition)
    : _simulator(simulator),
      _graphicsView(graphicsView),
      _removedBlockPosition(removedBlockPosition),
      _allBlocksPosition(allBlocksPosition),
      _playerPosition(playerPosition)
{
    setText("Block removed!");
}

void BlokRemovalCommand::undo()
{
    _simulator->removeAllBodies(false);
    //QMessageBox::information(nullptr, "TESTE", QString("#items: %1").arg(_graphicsView->scene()->items().size()));
    _simulator->recreate(_allBlocksPosition, _playerPosition);
}

void BlokRemovalCommand::redo()
{
    _simulator->removeBody(
        _graphicsView->scene()->itemAt(_removedBlockPosition, QTransform()),
        false
    );
}
