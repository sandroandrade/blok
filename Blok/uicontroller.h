#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include "../BlokInterfaces/iuicontroller.h"

class MainWindow;

class UIController : public IUIController
{
public:
    UIController(QObject *parent=nullptr);

    // IUIController interface
public:
    bool initialize();
    bool addMenuItem(const QString &menu, QAction *action);
    bool addToolButton(const QString &objectName, QAction *action);

private:
    MainWindow *_mainWindow;
};

#endif // UICONTROLLER_H
