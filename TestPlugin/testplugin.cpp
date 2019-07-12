#include "testplugin.h"

#include <QAction>
#include "../BlokInterfaces/icore.h"
#include "../BlokInterfaces/iuicontroller.h"

#include <QApplication>

TestPlugin::TestPlugin()
{
}

bool TestPlugin::initialize()
{
    IUIController *uiController = ICore::instance()->uiController();
    uiController->addMenuItem("File", new QAction("Open"));
    uiController->addMenuItem("File", new QAction("Save"));
    uiController->addMenuItem("Edit", new QAction("Copy"));
    uiController->addToolButton("MainToolBar",
                  new QAction(QIcon::fromTheme("document-open"),
                  "Open"));
    uiController->addToolButton("MainToolBar",
                  new QAction(QIcon::fromTheme("document-save"),
                  "Save"));
    QAction *exitAction = new QAction(QIcon::fromTheme("application-exit"),
                                      "Exit");
    uiController->addToolButton("SecondaryToolBar", exitAction);
    connect(exitAction, &QAction::triggered, []() { qApp->exit(); });

    return true;
}
