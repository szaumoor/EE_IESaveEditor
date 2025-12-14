#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopServices>
#include <QClipboard>
#include <QFileDialog>
#include <QString>
#include <QWidget>


MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    set_up_connections();
    set_up_shortcuts();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    quit();
}

void MainWindow::set_up_connections()
{
    connect( ui->actionAbout, &QAction::triggered, this, &MainWindow::show_about );
    connect( ui->actionForum, &QAction::triggered, this, &MainWindow::open_forum );
    connect( ui->actionGibberlings, &QAction::triggered, this, &MainWindow::open_discord_g3 );
    connect( ui->actionInfinityEngine, &QAction::triggered, this, &MainWindow::open_discord_ie );
    connect( ui->actionGitHub, &QAction::triggered, this, &MainWindow::open_github_repo );
    connect( ui->actionQuit, &QAction::triggered, this, &MainWindow::quit );
    connect( ui->actionOpen, &QAction::triggered, this, &MainWindow::open_file );
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_about()
{
    QMessageBox::information(
        this,
        "About",
        "<h2>EE Save Editor</h2>"
        "<p>Author: szaumoor, a.k.a. 'RoyalProtector'</p>"
        "<p>Contact: royalprotector@keemail.me</p>"
        "<p><a href='https://github.com/szaumoor'>My GitHub</a></p>"
        "<p>Version: 0.1</p>"
        "<p>Powered by C++ and the Qt Framework</p>"
    );
}

void MainWindow::open_file()
{
    const QString dir = QFileDialog::getExistingDirectory(
        this,
        tr( "Select folder" ),
        QString(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if ( dir.isEmpty() )
        qDebug() << "User cancelled";
    else
        qDebug() << "User selected" << dir;
}

void MainWindow::open_my_mods()
{
    QDesktopServices::openUrl( QUrl( "https://szaumoor.github.io/IEModLinks/" ) );
}

void MainWindow::open_forum()
{
    QDesktopServices::openUrl( QUrl( "https://www.gibberlings3.net/profile/12720-royalprotector/" ) );
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

void MainWindow::quit()
{
    const auto prompt = QMessageBox::question(
        this,
        "Warning",
        "Are you sure you want to quit the application? All unsaved changes will be lost."
    );

    if ( prompt == QMessageBox::StandardButton::Yes )
        QApplication::quit();
}
