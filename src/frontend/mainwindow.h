#ifndef EESAVEEDITOR_MAINWINDOW_H
#define EESAVEEDITOR_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "../backend/gam_file.h"
#include "../backend/tlk_file.h"

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
    std::optional<TlkFile> tlk;

private:
    Ui::MainWindow* ui;
    void closeEvent( QCloseEvent* event ) override;
    std::optional<GamFile> savegame { std::nullopt  };
    void set_up_connections();
    void set_up_shortcuts() const;

private slots:
    void show_about();
    void open_file();
    void reload_resources();
    static void open_forum();
    static void open_my_mods();
    static void open_discord_g3();
    static void open_discord_ie();
    static void open_github_repo();
};

#endif //EESAVEEDITOR_MAINWINDOW_H
