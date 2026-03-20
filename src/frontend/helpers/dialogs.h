#ifndef EE_SAVEEDITOR_DIALOGS_H
#define EE_SAVEEDITOR_DIALOGS_H

#include <QMessageBox>
#include <QString>
#include <QWidget>

class Dialogs
{
public:
    explicit Dialogs(QWidget* parent) : parent(parent){}

    void warn( const QString& message, const QString& title = "Warning" ) const
    {
        QMessageBox::warning(parent, title, message);
    }

    template<typename Function>
    void warn_and( const QString& message, const Function& func, const QString& title = "Warning" ) const
    {
        const auto prompt  = QMessageBox::warning(parent, title, message,
            QMessageBox::StandardButton::No | QMessageBox::StandardButton::Yes);

        func(prompt);
    }

    void info( const QString& message, const QString& title = "Information" ) const
    {
        QMessageBox::information(parent, title, message);
    }

    void error( const QString& message, const QString& title = "Error" ) const
    {
        QMessageBox::critical( parent, title, message );
    }

    void about( const QString& message, const QString& title = "About" ) const
    {
        QMessageBox::about( parent, title, message );
    }

private:
    QWidget* parent;
};

#endif //EE_SAVEEDITOR_DIALOGS_H