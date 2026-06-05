#include <QApplication>
#include <QIcon>
#include <QLocale>
#include <QScreen>
#include <QString>
#include <QStringList>
#include <QTranslator>

#include "frontend/mainwindow.h"

constexpr auto kAppName = "EE Save Editor";

bool install_translation(QTranslator& translator)
{
    const QStringList uiLanguages = QLocale::system().uiLanguages();
   // const QStringList uiLanguages = {"es_ES" };

    for ( const QString& localeName : uiLanguages )
    {
        const QLocale locale( localeName );

        if ( locale.language() == QLocale::English )
            continue;

        const QString exactLocale = locale.name();
        const QString language = exactLocale.section( '_', 0, 0 );
        QStringList candidates { exactLocale };

        if ( language != exactLocale )
            candidates << language;

        for ( const QString& candidate : candidates )
        {
            const QString translation = QStringLiteral( ":/translations/EE_SaveEditor_%1" ).arg( candidate );

            if ( translator.load( translation ) )
            {
                QApplication::installTranslator( &translator );
                qInfo() << "Loaded translation:" << translation;
                return true;
            }
        }
    }

    qInfo() << "Using default English UI.";
    return false;
}

inline void center_window( MainWindow& window )
{
    window.move( window.screen()->geometry().center() - window.rect().center() );
}

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    QApplication::setApplicationName( kAppName );
    QApplication::setApplicationDisplayName( kAppName );
    QApplication::setWindowIcon( QIcon( ":/img/shield.ico" ) );

    QTranslator translator;
    install_translation( translator );

    MainWindow window;
    center_window( window );
    window.show();
    return QApplication::exec();
}
