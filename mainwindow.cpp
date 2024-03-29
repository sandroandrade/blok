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

#include <simulator.h>

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

    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setMaximumSize(1000, 600);
    ui->graphicsView->setMinimumSize(1000, 600);
    ui->graphicsView->installEventFilter(this);

    _timer.setFrameRange(0, 100);
    _animation.setTimeLine(&_timer);

    _simulator = new Simulator(this);
    connect(_simulator, SIGNAL(bodiesCreated(QList<b2Body*>)),
                        SLOT(bodiesCreated(QList<b2Body*>)));
    connect(_simulator, SIGNAL(bodiesUpdated(QList<b2Body*>)),
                        SLOT(bodiesUpdated(QList<b2Body*>)));
    connect(this, SIGNAL(bodyClicked(b2Body*)),
            _simulator, SLOT(removeBody(b2Body*)));

    _initialState = new QState();
    _runningState = new QState();
    _youWonState  = new QState();
    _youLostState = new QState();

    connect(_initialState, SIGNAL(entered()), this, SLOT(init()));
    connect(_initialState, SIGNAL(entered()), _simulator, SLOT(init()));
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

    _stateMachine.addState(_initialState);
    _stateMachine.addState(_runningState);
    _stateMachine.addState(_youWonState);
    _stateMachine.addState(_youLostState);
    _stateMachine.setInitialState(_initialState);

    _stateMachine.start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
    _scene->clear();
    _scene->setSceneRect(-450, -250, 900, 500);

    // Background
    _scene->addPixmap(QPixmap (":/resources/images/background.png"))->setPos(-500, -300);

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
    QBrush brush(QPixmap(":/resources/images/ground.png"));
    brush.setTransform(brush.transform().translate(-450, -10));
    ground->setBrush(brush);
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
            {
                foreach(b2Body *body, m_bodyRect.keys())
                    if (m_bodyRect[body] == item && item != _player)
                    {
                        emit bodyClicked(body);
                        _scene->removeItem(item);
                        break;
                    }
            }
        }
    }
    if ((_stateMachine.configuration().contains(_initialState) ||
         _stateMachine.configuration().contains(_youWonState) ||
         _stateMachine.configuration().contains(_youLostState)) &&
         event->type() == QEvent::KeyPress && _timer.state() == QTimeLine::NotRunning)
        emit keyPressed();

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::bodiesUpdated(const QList<b2Body *> &bodies)
{
    foreach (b2Body *body, bodies)
    {
        const b2Vec2 &pos = body->GetPosition();
        m_bodyRect[body]->setPos(pos.x, -pos.y);
    }
}

void MainWindow::bodiesCreated(const QList<b2Body *> &bodies)
{
    m_bodyRect.clear();
    foreach (b2Body *body, bodies)
    {
        const b2Vec2 &position = body->GetPosition();
        QGraphicsRectItem *rect = 0;
        if (body->GetUserData())
        {
            // Player
            rect = _scene->addRect(-28, -28, 56, 56);
            QPixmap pixmap(QString(":/resources/images/player%1.png").arg(qrand()%9));
            QBrush brush(pixmap);
            brush.setTransform(brush.transform().translate(-28, -28));
            rect->setBrush(brush);
            _player = rect;
        }
        else
        {
            // Block
            rect = _scene->addRect(-14, -14, 28, 28);
            QBrush brush(QPixmap(":/resources/images/brick.png"));
            brush.setTransform(brush.transform().translate(-14, -14));
            rect->setBrush(brush);
        }
        rect->setPos(position.x, -position.y);
        rect->setPen(QPen(Qt::NoPen));

        m_bodyRect[body] = rect;
    }
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
