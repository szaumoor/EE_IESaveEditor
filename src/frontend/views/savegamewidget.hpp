#ifndef SAVEGAMEWIDGET_H
#define SAVEGAMEWIDGET_H

#include <optional>

#include "variable_table_model.hpp"

#include "../../backend/gam_file.hpp"

#include "../helpers/dialogs.hpp"

#include "../resources/resource_repository.hpp"

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
    void inject_data(const GamFile& file, ResourceRepository* res);
signals:
    void save_changed(const GamFile& file);

private:
    ResourceRepository* resources;
    std::optional<GamFile> gam { std:: nullopt };

    #pragma region UiSetup
    void update_member_slider() const;
    bool complete_ui(int index);
    void setup_tables();
    void setup_slider();
    void setup_style() const;
    Ui::SaveGameWidget* ui;
    Dialogs dlg;
    VariableTableModel* m_global_model = nullptr;
    VariableTableModel* m_local_model  = nullptr;
    #pragma endregion

    #pragma region PopulationMethods
    void populate_stats( const CreHeader& cre_header ) const;
    void populate_combat_stats( const CreHeader& cre_header ) const;
    void populate_misc_data( const CreHeader& cre_header ) const;
    void populate_armor_class( const CreHeader& cre_header ) const;
    void populate_resistances( const CreHeader& cre_header ) const;
    void populate_saving_throws( const CreHeader& cre_header ) const;
    void populate_thief_skills( const CreHeader& cre_header ) const;
    void populate_character_data( const GamCharacterData& char_data) const;
    void populate_party_metrics() const;
    #pragma endregion
};

#endif // SAVEGAMEWIDGET_H
