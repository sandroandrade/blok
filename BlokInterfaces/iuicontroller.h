#ifndef IUICONTROLLER_H
#define IUICONTROLLER_H

#include "blokinterfaces_global.h"

#include <QObject>

#include <QInputDialog>
#include <QComboBox>
#include <QGridLayout>

class QAction;
class QGraphicsItem;

class BLOKINTERFACESSHARED_EXPORT IUIController : public QObject
{
    Q_OBJECT
public:
    explicit IUIController(QObject *parent = nullptr);
    virtual bool initialize() = 0;
    virtual bool addMenuItem(const QString &menu, QAction *action) = 0;
    virtual bool addToolButton(const QString &objectName, QAction *action) = 0;
    virtual bool addGraphicsItem(QGraphicsItem *graphicsItem) = 0;
    template <typename T>
    T *selectPlugin(const QHash<QString, T *> &plugins) {
        bool ok;
        QString selectedPlugin = QInputDialog::getItem(nullptr,
                                 "Select a block builder plugin",
                                 "Available plugins",
                                 plugins.keys(),
                                 0, false, &ok);
        return (ok) ? plugins[selectedPlugin]:nullptr;
    }

Q_SIGNALS:
    void init();
    void blockRemoved();
};

#endif // IUICONTROLLER_H
