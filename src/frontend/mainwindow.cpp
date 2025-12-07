#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QClipboard>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::show_about);
    connect(ui->actionForum, &QAction::triggered, this, &MainWindow::open_forum);
    connect(ui->actionGibberlings, &QAction::triggered, this, &MainWindow::open_discord_g3);
    connect(ui->actionInfinityEngine, &QAction::triggered, this, &MainWindow::open_discord_ie);
    connect(ui->actionGitHub, &QAction::triggered, this, &MainWindow::open_github_repo);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quit);

    ui->actionQuit->setShortcut(QKeySequence(Qt::ALT | Qt::Key_X));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::show_about()
{
    QMessageBox::information(
        this,
        "About EE Save Editor",
        "Author: szaumoor\n"
        "Contact: royalprotector@keemail.me\n"
        "Version: 0.1\n"
        "Powered by C++ and the Qt Framework"
    );
}

void MainWindow::open_forum()
{
    QMessageBox::warning(
        this,
        "Forum",
        "Forum doesn't exist yet! Stay tuned."
    );
}

void MainWindow::open_discord_g3()
{
    if (const bool ok = QDesktopServices::openUrl(QUrl("https://discord.com/invite/yTzjMTb")); !ok)
    {
        qDebug() << "Error opening link to join discord!";
    }
}

void MainWindow::open_discord_ie()
{
    if (const bool ok = QDesktopServices::openUrl(QUrl("https://discord.gg/NWw65ags7S")); !ok)
    {
        qDebug() << "Error opening link to join discord!";
    }
}

void MainWindow::open_github_repo()
{
    if (const bool ok = QDesktopServices::openUrl(QUrl("https://github.com/szaumoor/EE_IESaveEditor")); !ok)
    {
        qDebug() << "Error opening link to visit github! Link copied to clipboard.";
        QApplication::clipboard()->setText("https://github.com/szaumoor/EE_IESaveEditor");
    }
}

void MainWindow::quit()
{
    const auto prompt = QMessageBox::question(
        this,
        "Warning",
        "Are you sure you want to quit the application? All unsaved changes will be lost."
    );

    if (prompt == QMessageBox::StandardButton::Yes)
        QApplication::quit();
}
