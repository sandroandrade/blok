#ifndef BLOKREMOVALCOMMAND_H
#define BLOKREMOVALCOMMAND_H

#include <QUndoCommand>
#include <QPointF>

class ISimulator;
class QGraphicsView;

class BlokRemovalCommand : public QUndoCommand
{
public:
    BlokRemovalCommand(ISimulator *simulator,
                       QGraphicsView *graphicsView,
                       QPointF removedBlockPosition,
                       QList<QPointF> allBlocksPosition,
                       QPointF playerPosition);

    void undo();
    void redo();

private:
    ISimulator *_simulator;
    QGraphicsView *_graphicsView;
    QPointF _removedBlockPosition;
    QList<QPointF> _allBlocksPosition;
    QPointF _playerPosition;
};

#endif // BLOKREMOVALCOMMAND_H
