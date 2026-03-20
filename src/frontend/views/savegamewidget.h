#ifndef SAVEGAMEWIDGET_H
#define SAVEGAMEWIDGET_H

#include <QWidget>
#include "../../backend/gam_file.h"

class GamFile;

namespace Ui {
    class SaveGameWidget;
}

class SaveGameWidget : public QWidget {
    Q_OBJECT

public:
    explicit SaveGameWidget(QWidget* parent = nullptr);
    ~SaveGameWidget() override;

private:
    Ui::SaveGameWidget* ui;
    std::optional<GamFile> gam { std:: nullopt };

public slots:
    void inject_data(const GamFile& file);

signals:
    void save_changed(const GamFile& file);
};

#endif // SAVEGAMEWIDGET_H
