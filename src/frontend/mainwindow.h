#ifndef EESAVEEDITOR_MAINWINDOW_H
#define EESAVEEDITOR_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};

#endif //EESAVEEDITOR_MAINWINDOW_H