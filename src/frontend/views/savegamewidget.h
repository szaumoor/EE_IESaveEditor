#ifndef SAVEGAMEWIDGET_H
#define SAVEGAMEWIDGET_H

#include <QWidget>

namespace Ui {
    class SaveGameWidget;
}

class SaveGameWidget : public QWidget {
    Q_OBJECT

public:
    explicit SaveGameWidget(QWidget* parent = nullptr);
    ~SaveGameWidget();

private:
    Ui::SaveGameWidget* ui;
};

#endif // SAVEGAMEWIDGET_H
