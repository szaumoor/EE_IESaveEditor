#include <QApplication>
#include <QLocale>
#include <QScreen>
#include <QTranslator>

#include "frontend/mainwindow.h"


inline void center_window( MainWindow& window )
{
    window.move( window.screen()->geometry().center() - window.rect().center() );
}

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    QTranslator translator; // auto-generated code for translations, unused for now
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for ( const QString &locale : uiLanguages )
    {
        const QString baseName = "EE_SaveEditor_" + QLocale( locale ).name();
        if ( translator.load( ":/translations/" + baseName ) )
            QApplication::installTranslator( &translator );
        break;
    }

    MainWindow window;
    center_window( window );
    window.show();

    return QApplication::exec();
}
