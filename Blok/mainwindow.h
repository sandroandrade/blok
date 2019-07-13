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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHash>
#include <QTimeLine>
#include <QStateMachine>
#include <QSharedPointer>

#include <QMainWindow>
#include <QGraphicsItemAnimation>

class QGraphicsScene;
class QGraphicsRectItem;
class QGraphicsTextItem;

namespace Ui
{
    class MainWindow;
}

class Simulator;
class ISkinFactory;
class ISimulator;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    bool initialize();

    bool addGraphicsItem(QGraphicsItem *graphicsItem);

Q_SIGNALS:
    void bodyClicked(QGraphicsItem *item);
    void keyPressed();
    void sceneInitialized();

public Q_SLOTS:
    void init();
    void bannerEnter();
    void bannerLeave();

private Q_SLOTS:
    void setBannerMessage(const QString &bannerMessage);
    void youWon();
    void youLost();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QSharedPointer<Ui::MainWindow> ui;
    QGraphicsScene *_scene;
    ISimulator *_simulator;

    QGraphicsRectItem *_banner;
    QGraphicsTextItem *_bannerMessage;
    QTimeLine _timer;
    QGraphicsItemAnimation _animation;

    QGraphicsRectItem *_player;

    QStateMachine _stateMachine;
    QState *_initialState;
    QState *_runningState;
    QState *_youWonState;
    QState *_youLostState;

    ISkinFactory *_selectedSkinFactory;
};

#endif // MAINWINDOW_H
