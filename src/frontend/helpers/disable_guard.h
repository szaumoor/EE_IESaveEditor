#ifndef EE_SAVEEDITOR_DISABLE_GUARD_H
#define EE_SAVEEDITOR_DISABLE_GUARD_H

#include <QWidget>

#include "disable_guard.h"

class UiDisableGuard : public QObject
{
    Q_OBJECT
public:
    UiDisableGuard( QObject* parent, const std::initializer_list<QWidget*> widgets)
        : QObject(parent), widgets(widgets)
    {
        for (auto* w : this->widgets)
            if (w) w->setEnabled(false);
    }

    ~UiDisableGuard() override
    {
        for (auto* w : widgets)
            if (w) w->setEnabled(true);
    }

private:
    QList<QWidget*> widgets;
};

#endif //EE_SAVEEDITOR_DISABLE_GUARD_H