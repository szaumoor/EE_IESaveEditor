#ifndef EE_SAVEEDITOR_DIALOGS_H
#define EE_SAVEEDITOR_DIALOGS_H

#include <QCoreApplication>
#include <QMessageBox>
#include <QString>
#include <QWidget>

class Dialogs
{
public:
    explicit Dialogs(QWidget* parent) : m_parent(parent){}

    void warn( const QString& message, const QString& title = {} ) const
    {
        QMessageBox::warning(m_parent, title.isEmpty() ? warning_title() : title, message);
    }

    template<typename Function>
    void warn_and( const QString& message, const Function& func, const QString& title = {} ) const
    {
        const auto prompt = QMessageBox::warning(m_parent, title.isEmpty() ? warning_title() : title, message,
            QMessageBox::StandardButton::No | QMessageBox::StandardButton::Yes);

        func(prompt);
    }

    void info( const QString& message, const QString& title = {} ) const
    {
        QMessageBox::information(m_parent, title.isEmpty() ? information_title() : title, message);
    }

    void error( const QString& message, const QString& title = {} ) const
    {
        QMessageBox::critical( m_parent, title.isEmpty() ? error_title() : title, message );
    }

    void about( const QString& message, const QString& title = {} ) const
    {
        QMessageBox::about( m_parent, title.isEmpty() ? about_title() : title, message );
    }

private:
    static QString warning_title()
    {
        return QCoreApplication::translate( "Dialogs", "Warning" );
    }

    static QString information_title()
    {
        return QCoreApplication::translate( "Dialogs", "Information" );
    }

    static QString error_title()
    {
        return QCoreApplication::translate( "Dialogs", "Error" );
    }

    static QString about_title()
    {
        return QCoreApplication::translate( "Dialogs", "About" );
    }

    QWidget* m_parent;
};

#endif //EE_SAVEEDITOR_DIALOGS_H
