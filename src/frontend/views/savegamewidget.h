#ifndef SAVEGAMEWIDGET_H
#define SAVEGAMEWIDGET_H

#include <optional>

#include "variable_table_model.h"

#include "../../backend/gam_file.h"
#include "../../backend/tlk_file.h"

#include "../helpers/dialogs.h"

#include <QWidget>

class GamFile;

namespace Ui {
    class SaveGameWidget;
}

class SaveGameWidget final : public QWidget {
    Q_OBJECT

public:
    explicit SaveGameWidget(QWidget* parent = nullptr);
    ~SaveGameWidget() override;

public slots:
    void inject_data(const GamFile& file, const TlkFile& tlk_file);
signals:
    void save_changed(const GamFile& file);

private:
    Ui::SaveGameWidget* ui;
    std::optional<GamFile> gam { std:: nullopt };
    std::optional<TlkFile> tlk { std::nullopt };
    Dialogs dlg;
    bool complete_ui(int index);
    VariableTableModel* m_global_model = nullptr;
    VariableTableModel* m_local_model = nullptr;
};

#endif // SAVEGAMEWIDGET_H
