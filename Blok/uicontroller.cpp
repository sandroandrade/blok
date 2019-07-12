#include "uicontroller.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>

#include "mainwindow.h"

UIController::UIController(QObject *parent)
    : IUIController(parent),
      _mainWindow(nullptr)
{
}

bool UIController::initialize()
{
    if (!_mainWindow) {
        _mainWindow = new MainWindow();
        _mainWindow->show();
        return true;
    }
    return false;
}

bool UIController::addMenuItem(const QString &menu, QAction *action)
{
    QMenu *myMenu = nullptr;
    for (auto menuBarAction : _mainWindow->menuBar()->actions())
        if (menuBarAction->menu()->title() == menu)
            myMenu = menuBarAction->menu();
    if (!myMenu)
        _mainWindow->menuBar()->addMenu(myMenu = new QMenu(menu));
    myMenu->addAction(action);
    return true;
}

bool UIController::addToolButton(const QString &objectName, QAction *action)
{
    QToolBar *myToolBar = nullptr;
    for (auto toolBar : _mainWindow->findChildren<QToolBar *>())
        if (toolBar->windowTitle() == objectName)
            myToolBar = toolBar;
    if (!myToolBar)
        _mainWindow->addToolBar(myToolBar = new QToolBar(objectName));
    myToolBar->addAction(action);
    return true;
}











