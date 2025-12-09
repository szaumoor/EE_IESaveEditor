#include <QApplication>
// #include <QLocale>
#include <QScreen>
// #include <QTranslator>

#include "frontend/mainwindow.h"


inline void center_window(MainWindow& window)
{
    window.move(window.screen()->geometry().center() - window.rect().center());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // QTranslator translator;
    // if (translator.load(QLocale(), "app", "_", ":src/frontend/translations")) {
    //     QApplication::installTranslator(&translator);
    // }
    //
    // auto a = QCoreApplication::translate("Menu", "FILE");
    // qDebug() << a;

    MainWindow window;
    center_window(window);
    window.show();

    return QApplication::exec();
}
