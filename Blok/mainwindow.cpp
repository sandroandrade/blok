/********************************************************************************
 *   Copyright (C) 2012 by Sandro Andrade <sandroandrade@kde.org>               *
 *                                                                              *
 *   This program is free software; you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or          *
 *   (at your option) any later version.                                        *
 *                                                                              *
 *   This program is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *   GNU General Public License for more details.                               *
 *                                                                              *
 *   You should have received a copy of the GNU General Public License          *
 *   along with this program; if not, write to the                              *
 *   Free Software Foundation, Inc.,                                            *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .             *
 *******************************************************************************/

#include "mainwindow.h"

#include <QTimer>
#include <QDebug>

#include <QBrush>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemAnimation>

#include <Box2D/Dynamics/b2Body.h>

#include <phonon4qt5/KDE/Phonon/MediaObject>

#include "ui_mainwindow.h"

#include "../BlokInterfaces/icore.h"
#include "../BlokInterfaces/iuicontroller.h"
#include "../BlokInterfaces/iplugincontroller.h"
#include "../BlokInterfaces/iskinfactory.h"
#include "../BlokInterfaces/iplugin.h"
#include "../BlokInterfaces/iblock.h"
#include "../BlokInterfaces/iblockbuilder.h"
#include "../BlokInterfaces/iground.h"
#include "../BlokInterfaces/ibackground.h"
#include "../BlokInterfaces/isimulator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _timer(500)
{
    qsrand(1);
    ui->setupUi(this);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    _scene = new QGraphicsScene;
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setMenuBar(new QMenuBar);

    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setMaximumSize(1000, 600);
    ui->graphicsView->setMinimumSize(1000, 600);
    ui->graphicsView->installEventFilter(this);

    _timer.setFrameRange(0, 100);
    _animation.setTimeLine(&_timer);

    _initialState = new QState();
    _runningState = new QState();
    _youWonState  = new QState();
    _youLostState = new QState();

    _stateMachine.addState(_initialState);
    _stateMachine.addState(_runningState);
    _stateMachine.addState(_youWonState);
    _stateMachine.addState(_youLostState);
    _stateMachine.setInitialState(_initialState);
}

MainWindow::~MainWindow()
{
}

bool MainWindow::initialize()
{
    _simulator = ICore::instance()->uiController()->selectPlugin(
        ICore::instance()->pluginController()->loadedPlugins<ISimulator>()
    );

    connect(this, &MainWindow::bodyClicked,
            _simulator, &ISimulator::removeBody);
    connect(_simulator, &ISimulator::blockRemoved,
            ICore::instance()->uiController(),
            &IUIController::blockRemoved);

    connect(_initialState, SIGNAL(entered()), this, SLOT(init()));
    connect(_initialState, SIGNAL(entered()), _simulator, SLOT(init()));

    connect(this, &MainWindow::sceneInitialized,
            ICore::instance()->uiController(), &IUIController::init);

    connect(_initialState, SIGNAL(entered()), this, SLOT(bannerEnter()));
    connect(_initialState, SIGNAL(exited()), this, SLOT(bannerLeave()));
    _initialState->addTransition(this, SIGNAL(keyPressed()), _runningState);

    connect(_runningState, SIGNAL(entered()), _simulator, SLOT(start()));
    _runningState->addTransition(_simulator, SIGNAL(youWon()), _youWonState);
    _runningState->addTransition(_simulator, SIGNAL(youLost()), _youLostState);

    connect(_youWonState, SIGNAL(entered()), this, SLOT(bannerEnter()));
    connect(_youWonState, SIGNAL(entered()), this, SLOT(youWon()));
    _youWonState->addTransition(this, SIGNAL(keyPressed()), _initialState);

    connect(_youLostState, SIGNAL(entered()), this, SLOT(bannerEnter()));
    connect(_youLostState, SIGNAL(entered()), this, SLOT(youLost()));
    _youLostState->addTransition(this, SIGNAL(keyPressed()), _initialState);

    _stateMachine.start();
    return true;
}

bool MainWindow::addGraphicsItem(QGraphicsItem *graphicsItem)
{
    _scene->addItem(graphicsItem);
    return true;
}

void MainWindow::init()
{
    _selectedSkinFactory = nullptr;
    do {
        _selectedSkinFactory = ICore::instance()->uiController()->selectPlugin(
            ICore::instance()->pluginController()->loadedPlugins<ISkinFactory>()
        );
    } while (!_selectedSkinFactory);

    IBlockBuilder *blockBuilder = nullptr;
    do {
        blockBuilder = ICore::instance()->uiController()->selectPlugin(
            ICore::instance()->pluginController()->loadedPlugins<IBlockBuilder>()
        );
    } while (!blockBuilder);

    _simulator->configure(_scene, blockBuilder, _selectedSkinFactory);

    _scene->clear();
    _scene->setSceneRect(-450, -250, 900, 500);

    // Background
    _scene->addPixmap(_selectedSkinFactory->createBackground()->pixmap())->setPos(-500, -300);

    // Banner
    _banner = _scene->addRect(-250, -50, 500, 100);
    _banner->setPos(800, -200);
    _banner->setBrush(QColor(0xDF, 0xC1, 0x01));

    _bannerMessage = new QGraphicsTextItem(_banner);
    _bannerMessage->setFont(QFont("Times", 18, QFont::Bold));
    _bannerMessage->setPos(-_bannerMessage->boundingRect().width()/2, -_bannerMessage->boundingRect().height()/1.25);

    QGraphicsTextItem *text2 = new QGraphicsTextItem("Press any key to start", _banner);
    text2->setFont(QFont("Times", 10, QFont::Bold));
    text2->setPos(-text2->boundingRect().width()/2, text2->boundingRect().height());

    // Ground
    QGraphicsRectItem *ground = _scene->addRect(-450, -10, 900, 20);
    ground->setPos(0, 260);
    QBrush brush(_selectedSkinFactory->createGround()->pixmap());
    brush.setTransform(brush.transform().translate(-450, -10));
    ground->setBrush(brush);

    emit sceneInitialized();
}

void MainWindow::bannerEnter()
{
    if(_stateMachine.configuration().contains(_initialState))
        setBannerMessage("Remove all the blocks but do not\nlet this guy hit the ground, okay ?");
    if(_stateMachine.configuration().contains(_youWonState))
        setBannerMessage("Congratulations ! You won !");
    if(_stateMachine.configuration().contains(_youLostState))
        setBannerMessage("I'm sorry, you lost ! Try again !");

    _animation.setItem(_banner);

    for (int i = 0; i < 200; ++i)
        _animation.setPosAt(i / 200.0, QPointF(800-i*4, -200));

    _timer.start();
}

void MainWindow::bannerLeave()
{
    _animation.setItem(_banner);

    for (int i = 0; i < 200; ++i)
        _animation.setPosAt(i / 200.0, QPointF(i*4, -200));

    _timer.start();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (_stateMachine.configuration().contains(_runningState) && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
        if (mouseEvent)
        {
            QPoint point =  mouseEvent->pos();
            QPointF scenePoint = ui->graphicsView->mapToScene(point);
            QGraphicsItem *item = ui->graphicsView->scene()->itemAt(scenePoint, QTransform());

            if (item)
                emit bodyClicked(item);
        }
    }
    if ((_stateMachine.configuration().contains(_initialState) ||
         _stateMachine.configuration().contains(_youWonState) ||
         _stateMachine.configuration().contains(_youLostState)) &&
         event->type() == QEvent::KeyPress && _timer.state() == QTimeLine::NotRunning)
        emit keyPressed();

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::setBannerMessage(const QString &bannerMessage)
{
    _bannerMessage->setPlainText(bannerMessage);
    _bannerMessage->setPos(-_bannerMessage->boundingRect().width()/2, -_bannerMessage->boundingRect().height()/1.25);
}

void MainWindow::youWon()
{
//    Phonon::MediaObject *audio = Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(":/resources/sounds/youwon.wav"));
//    connect(audio, SIGNAL(finished()), audio, SLOT(deleteLater()));
//    audio->play();
}

void MainWindow::youLost()
{
//    Phonon::MediaObject *audio = Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(":/resources/sounds/youlost.wav"));
//    connect(audio, SIGNAL(finished()), audio, SLOT(deleteLater()));
//    audio->play();
}
