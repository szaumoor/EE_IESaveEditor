#include <QApplication>
#include <QLocale>
#include <QScreen>
#include <QString>
#include <QTranslator>

#include "frontend/mainwindow.h"
#include "frontend/profiles/constants.h"


Game::Language::Instance detect_system_language()
{
    for (const QString& localeName : QLocale::system().uiLanguages())
    {
        const auto lang = Game::Language::lang_from_locale(QLocale(localeName));

        if (lang != Game::Language::Instance::English)
            return lang;
    }

    return Game::Language::Instance::English;
}

bool install_translation(QTranslator& translator, const Game::Language::Instance lang)
{
    if (lang == Game::Language::Instance::English)
    {
        qInfo() << "Using default English UI.";
        return false;
    }

    const QString code = Game::Language::code_for_lang(lang);
    const QString translation =
        QStringLiteral(":/translations/EE_SaveEditor_%1").arg(code);

    if (translator.load(translation))
    {
        QApplication::installTranslator(&translator);
        qInfo() << "Loaded translation:" << translation;
        return true;
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
    QApplication::setApplicationName( consts::settings::kAppName );
    QApplication::setApplicationDisplayName( consts::settings::kAppName );
    QApplication::setWindowIcon( QIcon( ":/img/shield.ico" ) );
    QTranslator translator;
    const auto language = detect_system_language();
    install_translation( translator, language );
    MainWindow window(language);
    center_window( window );
    window.show();
    return QApplication::exec();
}
