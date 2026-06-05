#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QFileDialog>
#include <QIcon>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QWidget>

#include <tuple>

#include "../backend/biff_file.h"
#include "../backend/key_file.h"

#include "helpers/gui_helpers.h"
#include "helpers/qt_io.h"

class KeyFile;
class BiffFile;

using ResourceResults = std::tuple<
    Possible<TlkFile>,
    Possible<BiffFile>,
    Possible<KeyFile>
>;

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent ), ui( new Ui::MainWindow ), dlg(this)
{
    ui->setupUi( this );
    setup_tray_icon();
    ui->savegame_widget->setVisible( false );
    set_up_connections();
    set_up_shortcuts();
    QTimer::singleShot(0, this, &MainWindow::reload_resources);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (not savegame)
    {
        event->accept();
        return;
    }

    dlg.warn_and(tr("Are you sure you want to quit the application? All unsaved changes will be lost."),
     [&event](const auto& prompt) {
         if ( prompt == QMessageBox::StandardButton::Yes )
             event->accept();
         else
             event->ignore();
     });
}

void MainWindow::set_up_connections()
{
    connect( ui->actionAbout, &QAction::triggered, this, &MainWindow::show_about );
    connect( ui->actionModForum, &QAction::triggered, this, &MainWindow::open_forum );
    connect( ui->actionMyProfile, &QAction::triggered, this, &MainWindow::open_forum_profile );
    connect( ui->actionGibberlings, &QAction::triggered, this, &MainWindow::open_discord_g3 );
    connect( ui->actionInfinityEngine, &QAction::triggered, this, &MainWindow::open_discord_ie );
    connect( ui->actionKaelynsMods, &QAction::triggered, this, &MainWindow::open_discord_my_mods );
    connect( ui->actionGitHub, &QAction::triggered, this, &MainWindow::open_github_repo );
    connect( ui->actionQuit, &QAction::triggered, this, QApplication::quit );
    connect( ui->actionOpen, &QAction::triggered, this, &MainWindow::open_file );
    connect( ui-> openFromToolbar, &QAction::triggered, this, &MainWindow::open_file );
    connect( ui->actionReload, &QAction::triggered, this, &MainWindow::reload_resources );
    connect( ui-> actionAboutQt, &QAction::triggered, QApplication::aboutQt);
    connect( ui-> actionMyMods, &QAction::triggered, this, &MainWindow::open_my_mods );
}

void MainWindow::set_up_shortcuts() const
{
    ui->actionOpen->setShortcut( QKeySequence( Qt::CTRL | Qt::Key_O ) );
    ui->actionOpen->setShortcutContext( Qt::ApplicationShortcut );

    ui->actionQuit->setShortcut( QKeySequence( Qt::CTRL | Qt::Key_Q ) );
    ui->actionQuit->setShortcutContext( Qt::ApplicationShortcut );

    ui->actionSave->setShortcut( QKeySequence( Qt::CTRL | Qt::Key_S ) );
    ui->actionSave->setShortcutContext( Qt::ApplicationShortcut );
}

void MainWindow::load_ui() const
{
    if (!savegame)
        return;

    ui->savegame_widget->inject_data( savegame.value(), tlk.value() );
    ui->savegame_widget->setVisible( true );
}

void MainWindow::set_always_on_top(const bool enabled)
{
    setWindowFlag(Qt::WindowStaysOnTopHint, enabled);
    show();
}

void MainWindow::show_about() const
{
    dlg.about(tr("<h2>EE Save Editor</h2>"
        "<p>Author: szaumoor, a.k.a. 'Kaelyn'</p>"
        "<p>Contact: kaelyn@tuta.io</p>"
        "<p><a href='https://github.com/szaumoor'>My GitHub</a></p>"
        "<p>Version: 0.1</p>"
        "<p>Powered by C++ and the Qt Framework</p>"));
}

void MainWindow::open_file()
{
    const QString path = QFileDialog::getExistingDirectory(
        this,
        tr( "Select folder" ),
        QString("/home/marcos/.local/share/Baldur's Gate II - Enhanced Edition/save"),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if ( path.isEmpty() )
        return;

    const auto gamPath = extend_path( {path, "BALDUR.gam"} );

    if (auto gam = GamFile::open( gamPath.toStdString() ))
    {
        savegame.emplace(gam.value());
    }

    load_ui();
}

void MainWindow::reload_resources()
{
    run_task_with_progress<ResourceResults>(this,
    {ui->menubar, ui->toolBar, ui->savegame_widget}, tr("Loading resources..."),
    [] {
        return std::make_tuple(
            TlkFile::open(TEST_RES_DIR "/dialog.tlk"),
            BiffFile::open(TEST_RES_DIR "/Spells.bif"),
            KeyFile::open(TEST_RES_DIR "/chitin.key")
        );
    },
    [this](ResourceResults results)
    {
        auto [get_tlk, biff, key] = results;

        if (get_tlk)
        {
            qInfo() << "TLK OK";
            tlk.emplace(get_tlk.value());
        }

        if (biff) qInfo() << "BIFF OK";
        if (key)  qInfo() << "KEY OK";
    });
}

void MainWindow::setup_tray_icon()
{
    using ActivationReason = QSystemTrayIcon::ActivationReason;
    trayIcon = new QSystemTrayIcon(QIcon(":/img/shield.ico"), this);
    auto * trayMenu = new QMenu(this);
    auto* alwaysOnTop = trayMenu->addAction(tr("Always on top"));
    alwaysOnTop->setCheckable(true);
    connect(alwaysOnTop, &QAction::toggled, this, &MainWindow::set_always_on_top);
    trayMenu->addAction(tr("Quit"), this, &QApplication::quit);
    trayIcon->setContextMenu( trayMenu );
    connect(trayIcon, &QSystemTrayIcon::activated, this,
    [this]( const ActivationReason reason) {
            if (reason != QSystemTrayIcon::Trigger && reason != QSystemTrayIcon::DoubleClick)
                return;

            if (isMinimized())
                showNormal();
            else
                show();
        raise();
        activateWindow();
    });

    trayIcon->show();
}

void MainWindow::open_forum()
{
    if ( !open_url( "https://www.gibberlings3.net/forums/topic/41304-ee-save-editor-new-save-editor-unreleased/" ) )
        qDebug() << "Error opening link to open mod forum!";
}

void MainWindow::open_forum_profile()
{
    if ( !open_url( "https://www.gibberlings3.net/profile/12720-kaelyn/" ) )
        qDebug() << "Error opening link to open mod forum!";
}

void MainWindow::open_my_mods()
{
    if ( !open_url("https://szaumoor.github.io/IEModLinks/" ) )
        qDebug() << "Error opening link to my mods!";
}

void MainWindow::open_discord_g3()
{
    if ( !open_url( "https://discord.com/invite/yTzjMTb" ) )
        qDebug() << "Error opening link to join discord!";
}

void MainWindow::open_discord_ie()
{
    if ( !open_url( "https://discord.gg/NWw65ags7S" ) )
        qDebug() << "Error opening link to join discord!";
}

void MainWindow::open_github_repo()
{
    if ( !open_url( "https://github.com/szaumoor/EE_IESaveEditor" ) )
    {
        qDebug() << "Error opening link to visit github! Link copied to clipboard.";
        QApplication::clipboard()->setText( "https://github.com/szaumoor/EE_IESaveEditor" );
    }
}

void MainWindow::open_discord_my_mods()
{
    if ( !open_url( "https://discord.gg/DER6Ma92X4" ) )
        qDebug() << "Error opening link to join discord!";
}
