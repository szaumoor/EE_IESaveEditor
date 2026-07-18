#ifndef EESAVEEDITOR_MAINWINDOW_H
#define EESAVEEDITOR_MAINWINDOW_H

#include <memory>
#include <optional>

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QWidget>

#include "../backend/gam_file.h"
#include "../backend/tlk_file.h"

#include "helpers/dialogs.h"
#include "profiles/games.h"

using TlkRef = std::shared_ptr<const TlkFile>;

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
    explicit MainWindow( Game::Language::Instance lang, QWidget* parent = nullptr );
    ~MainWindow() override;

protected:
    void closeEvent( QCloseEvent* event ) override;

private:
    TlkRef tlk;
    std::optional<GamFile> savegame { std::nullopt  };

    #pragma region UiSetup
    Dialogs dlg;
    QSystemTrayIcon* trayIcon = nullptr;
    Ui::MainWindow* ui;
    void set_up_connections();
    void set_up_shortcuts() const;
    void load_ui() const;
    void manage_language_actions(Game::Language::Instance lang);
    void set_always_on_top(bool enabled);
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
    #pragma endregion
};

#endif //EESAVEEDITOR_MAINWINDOW_H
