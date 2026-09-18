#ifndef EESAVEEDITOR_MAINWINDOW_H
#define EESAVEEDITOR_MAINWINDOW_H

#include <memory>
#include <optional>

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QWidget>

#include "../backend/gam_file.hpp"

#include "helpers/dialogs.hpp"
#include "profiles/games.hpp"
#include "resources/resource_repository.hpp"

using ResourceRef = std::unique_ptr<ResourceRepository>;

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
    explicit MainWindow( Language language, QWidget* parent = nullptr );
    ~MainWindow() override;

protected:
    void closeEvent( QCloseEvent* event ) override;

private:
    ResourceRef resources;
    std::optional<GamFile> savegame { std::nullopt  };
    Language lang;

    #pragma region UiSetup
    Dialogs dlg;
    QSystemTrayIcon* trayIcon = nullptr;
    QMenu* trayMenu = nullptr;
    QAction* trayAlwaysOnTop = nullptr;
    Ui::MainWindow* ui;
    void set_up_connections();
    void set_up_shortcuts() const;
    void load_ui() const;
    void manage_language_actions(Language new_lang);

    void set_always_on_top_connections();
    void setup_tray_icon();
    #pragma endregion

private slots:
    void open_file();
    void reload_resources();

    #pragma region Actions
    void show_about() const;
    static void open_forum();
    static void open_forum_profile();
    static void open_my_mods();
    static void open_discord_g3();
    static void open_discord_ie();
    static void open_github_repo();
    static void open_discord_my_mods();
    void always_on_top(bool enabled);
    #pragma endregion
};

#endif //EESAVEEDITOR_MAINWINDOW_H
