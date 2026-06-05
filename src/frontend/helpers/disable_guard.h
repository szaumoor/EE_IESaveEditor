#ifndef EE_SAVEEDITOR_DISABLE_GUARD_H
#define EE_SAVEEDITOR_DISABLE_GUARD_H

#include <QWidget>

class UiDisableGuard : public QObject
{
    Q_OBJECT
public:
    UiDisableGuard( QObject* parent, const std::initializer_list<QWidget*> widgets)
        : QObject(parent), m_widgets(widgets)
    {
        for (auto* w : this->m_widgets)
            if (w) w->setEnabled(false);
    }

    ~UiDisableGuard() override
    {
        for (auto* w : m_widgets)
            if (w) w->setEnabled(true);
    }

private:
    QList<QWidget*> m_widgets;
};

#endif //EE_SAVEEDITOR_DISABLE_GUARD_H