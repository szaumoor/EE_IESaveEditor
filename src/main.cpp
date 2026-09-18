#include <QScreen>
#include <QTranslator>

#include "frontend/mainwindow.hpp"
#include "frontend/helpers/gui_helpers.hpp"
#include "frontend/profiles/constants.hpp"
#include "frontend/resources/resource_repository.hpp"


static Language detect_system_language()
{
    for (const QString& localeName : QLocale::system().uiLanguages())
    {
        if (
            const auto lang = lang_from_locale(QLocale(localeName));
            lang != Language::English
        ) {
            return lang;
        }
    }
    return Language::English;
}

static bool install_translation(QTranslator& translator, const Language lang)
{
    if (lang == Language::English)
    {
        qInfo() << "Using default English UI.";
        return false;
    }

    const auto code = code_for_lang(lang);
    if (!code) {
        qInfo() << "Language not recognized, defaulting to English UI";
        return false;
    }

    const QString translation =
        QStringLiteral(":/translations/EE_SaveEditor_%1").arg(*code);

    if (translator.load(translation))
    {
        QApplication::installTranslator(&translator);
        qInfo() << "Loaded translation:" << translation;
        return true;
    }

    return false;
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
    gui::center_window( window );
    window.show();

    return QApplication::exec();
}
