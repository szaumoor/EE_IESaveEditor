#ifndef EESAVEEDITOR_MAINWINDOW_H
#define EESAVEEDITOR_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;

    void set_up_connections();
    void set_up_shortcuts() const;

private slots:
    void quit();
    void show_about();
    void open_file();
    static void open_forum();
    static void open_my_mods();
    static void open_discord_g3();
    static void open_discord_ie();
    static void open_github_repo();
};

#endif //EESAVEEDITOR_MAINWINDOW_H
