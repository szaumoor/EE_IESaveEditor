#include <QApplication>
#include <QScreen>

#include "frontend/mainwindow.h"


inline auto center_window(QMainWindow& window) -> void
{
    window.move(window.screen()->geometry().center() - window.rect().center());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    center_window(window);
    window.show();

    return QApplication::exec();
}
