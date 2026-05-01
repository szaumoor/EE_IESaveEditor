#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../backend/biff_file.h"
#include "../backend/key_file.h"

#include <QClipboard>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QWidget>

#include <tuple>

#include "helpers/gui_helpers.h"
#include "helpers/qt_io.h"

class KeyFile;
class BiffFile;

using ResourceResults = std::tuple<
    Possible<TlkFile>,
    Possible<BiffFile>,
    Possible<KeyFile>
>;

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow ), dlg(this)
{
    ui->setupUi( this );
    ui->widget->setVisible( false );
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

    dlg.warn_and("Are you sure you want to quit the application? All unsaved changes will be lost.",
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
    connect( ui->actionGibberlings, &QAction::triggered, this, &MainWindow::open_discord_g3 );
    connect( ui->actionInfinityEngine, &QAction::triggered, this, &MainWindow::open_discord_ie );
    connect( ui->actionGitHub, &QAction::triggered, this, &MainWindow::open_github_repo );
    connect( ui->actionQuit, &QAction::triggered, this, QApplication::quit );
    connect( ui->actionOpen, &QAction::triggered, this, &MainWindow::open_file );
    connect( ui-> openFromToolbar, &QAction::triggered, this, &MainWindow::open_file );
    connect( ui->actionReload, &QAction::triggered, this, &MainWindow::reload_resources );
    connect( ui-> actionAboutQt, &QAction::triggered, QApplication::aboutQt);
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

    ui->widget->inject_data( savegame.value() );
    ui->widget->setVisible( true );
}

void MainWindow::show_about() const
{
    dlg.about("<h2>EE Save Editor</h2>"
        "<p>Author: szaumoor, a.k.a. 'Kaelyn'</p>"
        "<p>Contact: kaelyn@tuta.io</p>"
        "<p><a href='https://github.com/szaumoor'>My GitHub</a></p>"
        "<p>Version: 0.1</p>"
        "<p>Powered by C++ and the Qt Framework</p>");
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
    auto gam = GamFile::open( gamPath.toStdString() );

    if (gam)
    {
        savegame.emplace(gam.value());
    }

    load_ui();
}



void MainWindow::reload_resources()
{
    run_task_with_progress<ResourceResults>(this,{ui->menubar, ui->toolBar},"Loading resources...",
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

void MainWindow::open_forum()
{
    QDesktopServices::openUrl( QUrl( "https://www.gibberlings3.net/profile/12720-kaelyn/" ) );
}

void MainWindow::open_my_mods()
{
    QDesktopServices::openUrl( QUrl( "https://szaumoor.github.io/IEModLinks/" ) );
}

void MainWindow::open_discord_g3()
{
    if ( const bool ok = QDesktopServices::openUrl( QUrl( "https://discord.com/invite/yTzjMTb" ) ); !ok )
    {
        qDebug() << "Error opening link to join discord!";
    }
}

void MainWindow::open_discord_ie()
{
    if ( const bool ok = QDesktopServices::openUrl( QUrl( "https://discord.gg/NWw65ags7S" ) ); !ok )
    {
        qDebug() << "Error opening link to join discord!";

    }
}

void MainWindow::open_github_repo()
{
    if ( const bool ok = QDesktopServices::openUrl( QUrl( "https://github.com/szaumoor/EE_IESaveEditor" ) ); !ok )
    {
        qDebug() << "Error opening link to visit github! Link copied to clipboard.";
        QApplication::clipboard()->setText( "https://github.com/szaumoor/EE_IESaveEditor" );
    }
}
