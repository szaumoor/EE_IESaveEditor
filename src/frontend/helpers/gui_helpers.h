#ifndef EE_SAVEEDITOR_UI_HELPERS_H
#define EE_SAVEEDITOR_UI_HELPERS_H

#include <initializer_list>

#include <QFutureWatcher>
#include <QProgressDialog>
#include <QtConcurrentRun>
#include <QDesktopServices>

#include "disable_guard.h"

inline auto infinite_progress_dialog( QWidget* parent, const QString& message )
{
    auto* progress = new QProgressDialog(message, QString(), 0, 0, parent);
    progress->setWindowModality(Qt::ApplicationModal);
    progress->setCancelButton(nullptr);
    progress->setMinimumDuration(0);
    return progress;
}

template <typename Result, typename Task, typename OnFinished>
void run_task_with_progress(QWidget* parent, const std::initializer_list<QWidget*> managed_widgets,
                            const QString& message, Task&& task, OnFinished&& onFinished)
{
    auto* ui_guard = new UiDisableGuard(parent, managed_widgets);
    auto* progress = infinite_progress_dialog(parent, message);
    progress->show();

    auto future = QtConcurrent::run(std::forward<Task>(task));
    auto* watcher = new QFutureWatcher<Result>(parent);
    QObject::connect(watcher, &QFutureWatcher<Result>::finished, parent,
    [watcher, progress, onFinished = std::forward<OnFinished>(onFinished), ui_guard] mutable
        {
            Result result = watcher->result();
            onFinished(result);
            progress->close();
            progress->deleteLater();
            watcher->deleteLater();
            ui_guard->deleteLater();
        }
    );
    watcher->setFuture(future);
}

inline bool open_url( const QString& url )
{
    return QDesktopServices::openUrl( QUrl(url));
}

#endif //EE_SAVEEDITOR_UI_HELPERS_H