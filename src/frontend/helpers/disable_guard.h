#ifndef EE_SAVEEDITOR_DISABLE_GUARD_H
#define EE_SAVEEDITOR_DISABLE_GUARD_H

#include <QPointer>
#include <QWidget>

class UiDisableGuard : public QObject
{
    Q_OBJECT
public:
    UiDisableGuard( QObject* parent, const std::initializer_list<QWidget*> widgets)
        : QObject(parent)
    {
        for (auto* w : widgets)
        {
            if (!w)
                continue;

            m_widgets.append(QPointer(w));
            w->setEnabled(false);
        }
    }

    ~UiDisableGuard() override
    {
        for ( const auto& w : m_widgets )
            if (w)
                w->setEnabled(true);
    }

private:
    QList<QPointer<QWidget>> m_widgets;
};

#endif //EE_SAVEEDITOR_DISABLE_GUARD_H