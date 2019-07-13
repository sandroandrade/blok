#include "blokscoreplugin.h"

#include <QGraphicsTextItem>

#include "../BlokInterfaces/icore.h"
#include "../BlokInterfaces/iuicontroller.h"

BlokScorePlugin::BlokScorePlugin()
    : _textItem(nullptr),
      _counter(0)
{
}

bool BlokScorePlugin::initialize()
{
    connect(ICore::instance()->uiController(), &IUIController::blockRemoved,
            this, &BlokScorePlugin::blockRemoved);
    connect(ICore::instance()->uiController(), &IUIController::init,
            this, &BlokScorePlugin::init);

    return true;
}

void BlokScorePlugin::blockRemoved()
{
    _textItem->setPlainText(QString::number(++_counter));
}

void BlokScorePlugin::init()
{
    _counter = 0;
    _textItem = new QGraphicsTextItem();
    _textItem->setFont(QFont("Times", 30, QFont::Bold));
    _textItem->setPlainText("0");
    _textItem->setPos(400, -200);
    ICore::instance()->uiController()->addGraphicsItem(_textItem);
}
