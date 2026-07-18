#include "savegamewidget.h"
#include "ui_savegamewidget.h"
#include "css.h"

#include "../../backend/tlk_file.h"

#include <QShortcut>

#include "../helpers/qt_strings.h"

using std::in_range;

SaveGameWidget::SaveGameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::SaveGameWidget), dlg(this)
{
    ui->setupUi(this);
    setup_tables();
    setup_slider();
    setup_style();
}

SaveGameWidget::~SaveGameWidget()
{
    delete ui;
}

void SaveGameWidget::inject_data( const GamFile& file, TlkRef tlk_file )
{
    gam.emplace( file );

    if (!gam)
    {
        dlg.error(tr("Error loading data into the UI"));
        return;
    }

    tlk = std::move(tlk_file);

    if (!tlk)
    {
        dlg.error(tr("Error loading TLK file"));
        return;
    }

    populate_party_metrics();
    m_global_model->set_variables( gam->globals() );

    complete_ui(0);
}

#pragma region UiSetup

void SaveGameWidget::update_member_slider() const
{
    if ( const auto size = gam->party_members().size(); size == 1)
        ui->slider_pmember->hide();
    else
    {
        ui->slider_pmember->setRange(0, static_cast<int>(size - 1));
        ui->slider_pmember->setVisible(true);
    }
}

bool SaveGameWidget::complete_ui(const int index)
{
    if ( !in_range<u32>(index) )
        return false;

    update_member_slider();

    const auto& members     = gam->party_members();
    const auto& cre_members = gam->party_members_cre();

    const auto uindex = static_cast<u32>(index);
    const auto& party_member = members[uindex];
    const auto& cre_party_member = cre_members[uindex];
    const auto& cre_header = cre_party_member.header();

    populate_combat_stats(cre_header);
    populate_thief_skills( cre_header );
    populate_misc_data( cre_header );
    populate_character_data( party_member );

    m_local_model->set_variables( cre_party_member.locals() );

    if (cre_header.short_name == static_cast<u32>(-1))
        ui->name_label->setText( str::from(party_member.character_name) );
    else {
        const auto str_ref = tlk->at( cre_header.short_name );
        const auto exists = str_ref.has_value();
        ui->name_label->setText( exists ?
            str::from( str_ref.value()) : str::from(str_ref.error())
        );
    }

    setEnabled( true );
    return true;
}

void SaveGameWidget::setup_tables()
{
    m_global_model = new VariableTableModel(this);
    ui->globals_table->setModel( m_global_model );
    ui->globals_table->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->globals_table->setSelectionMode( QAbstractItemView::SingleSelection );

    m_local_model = new VariableTableModel(this);
    ui->locals_table->setModel( m_local_model );
    ui->locals_table->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->locals_table->setSelectionMode( QAbstractItemView::SingleSelection );

    const auto* deleteShortcut = new QShortcut(QKeySequence::Delete, ui->globals_table);

    connect(deleteShortcut, &QShortcut::activated, this, [this] {
        const QModelIndex current = ui->globals_table->currentIndex();

        if (!current.isValid())
            return;

        dlg.warn_and( tr("Are you sure you want to delete this variable?"), [&](auto response) {
            if (response == QMessageBox::StandardButton::Yes)
                ui->globals_table->model()->removeRow(current.row());
        } );
    });

    ui->globals_table->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    ui->locals_table->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
}

void SaveGameWidget::setup_slider()
{
    auto* decrease_shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Left), this);
    decrease_shortcut->setContext(Qt::WindowShortcut);

    connect(decrease_shortcut, &QShortcut::activated, this, [this] {
        ui->slider_pmember->setValue(ui->slider_pmember->value() - ui->slider_pmember->singleStep());
    });

    auto* increase_shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Right), this);
    increase_shortcut->setContext(Qt::WindowShortcut);

    connect(increase_shortcut, &QShortcut::activated, this, [this] {
        ui->slider_pmember->setValue(ui->slider_pmember->value() + ui->slider_pmember->singleStep());
    });

    connect( ui->slider_pmember, &QSlider::valueChanged, this, [this] {
        const auto slider_value = ui->slider_pmember->value();
        complete_ui( slider_value );
    } );

    auto slider_policy = ui->slider_pmember->sizePolicy();
    slider_policy.setRetainSizeWhenHidden( true );
    ui->slider_pmember->setSizePolicy(slider_policy);
}

void SaveGameWidget::setup_style() const
{
    ui->tabWidget->setStyleSheet(css::kTabWidget);
    ui->slider_pmember->setStyleSheet(css::kPartyMemberSlider);
}

#pragma endregion

#pragma region PopulationMethods

void SaveGameWidget::populate_stats( const CreHeader& cre_header ) const
{
    const auto [strength,
        strength_bonus,
        intelligence,
        wisdom,
        dexterity,
        constitution,
        charisma
    ] = cre_header.stats;

    ui->stat_strength->setValue( strength );
    ui->stat_str_extra->setValue( strength_bonus );
    ui->stat_dexterity->setValue( dexterity );
    ui->stat_constitution->setValue( constitution );
    ui->stat_intelligence->setValue( intelligence );
    ui->stat_wisdom->setValue( wisdom );
    ui->stat_charisma->setValue( charisma );
}

void SaveGameWidget::populate_combat_stats( const CreHeader& cre_header ) const
{
    populate_stats( cre_header );
    populate_armor_class(cre_header);
    populate_resistances(cre_header);
    populate_saving_throws(cre_header);

    ui->stat_base_thac0->setValue( cre_header.thac0 );
    ui->stat_first_level->setValue(cre_header.class_levels[0]);
    ui->stat_second_level->setValue(cre_header.class_levels[1]);
    ui->stat_third_level->setValue(cre_header.class_levels[2]);
    ui->stat_cur_hp->setValue( cre_header.current_hit_points );
    ui->stat_max_hp->setValue( cre_header.max_hit_points );
}

void SaveGameWidget::populate_misc_data( const CreHeader& cre_header ) const
{
    ui->stat_lore->setValue(cre_header.lore);
    ui->stat_intoxication->setValue(cre_header.intoxication);
    ui->stat_morale->setValue(cre_header.morale);
    ui->stat_morale_break->setValue(cre_header.morale_break);
    ui->stat_morale_rec->setValue(cre_header.morale_recovery_time);
    ui->stat_fatigue->setValue(cre_header.fatigue);
    ui->stat_xp->setValue( static_cast<i32>(cre_header.xp_gained_kills) );
    ui->stat_xp_for_kill->setValue( static_cast<i32>(cre_header.xp_creature) );

    ui->stat_class->setValue(cre_header.clazz);
    ui->stat_kit->setValue( static_cast<i32>(cre_header.kit_id) );
    ui->stat_alignment->setValue(cre_header.alignment);
    ui->stat_racial_enemy->setValue( cre_header.racial_enemy );
    ui->stat_gender->setValue(cre_header.gender);
    ui->stat_race->setValue(cre_header.race);
    ui->stat_sex_voice->setValue( cre_header.sex );
}

void SaveGameWidget::populate_armor_class( const CreHeader& cre_header ) const
{
    const auto [ac_natural,
        ac_effective,
        ac_crushing,
        ac_missile,
        ac_piercing,
        ac_slashing
    ] = cre_header.armor_class;

    ui->ac_base->setValue( ac_effective );
    ui->ac_effective->setValue( ac_effective );
    ui->ac_piercing->setValue( ac_piercing );
    ui->ac_crush->setValue( ac_crushing );
    ui->ac_slashing->setValue( ac_slashing );
    ui->ac_missile->setValue( ac_missile );
}

void SaveGameWidget::populate_resistances( const CreHeader& cre_header ) const
{
    const auto [resist_fire,
        resist_cold,
        resist_electricity,
        resist_acid,
        resist_magic,
        resist_magic_fire,
        resist_magic_cold,
        resist_slashing,
        resist_crushing,
        resist_piercing,
        resist_missile
    ] = cre_header.resistances;

    ui->resist_acid->setValue(resist_acid);
    ui->resist_cold->setValue(resist_cold);
    ui->resist_electric->setValue(resist_electricity);
    ui->resist_fire->setValue(resist_fire);
    ui->resist_magic->setValue(resist_magic);
    ui->resist_magic_cold->setValue( resist_magic_cold );
    ui->resist_magic_fire->setValue( resist_magic_fire);
    ui->resist_missile->setValue( resist_missile );
    ui->resist_piercing->setValue( resist_piercing );
    ui->resist_slashing->setValue( resist_slashing );
    ui->resist_crush->setValue( resist_crushing );
    ui->resist_missile->setValue( resist_missile  );
}

void SaveGameWidget::populate_saving_throws( const CreHeader& cre_header ) const
{
    const auto [saving_throw_vs_death,
        saving_throw_vs_wands,
        saving_throw_vs_poly,
        saving_throw_vs_breath,
        saving_throw_vs_spell
    ] = cre_header.saving_throws;

    ui->save_death->setValue( saving_throw_vs_death);
    ui->save_wand->setValue( saving_throw_vs_wands);
    ui->save_poly->setValue(saving_throw_vs_poly);
    ui->save_breath->setValue(saving_throw_vs_breath);
    ui->save_spell->setValue(saving_throw_vs_spell);
}

void SaveGameWidget::populate_thief_skills( const CreHeader& cre_header ) const
{
    ui->stat_hide_shadows->setValue(cre_header.hide_in_shadows);
    ui->stat_move_silently->setValue(cre_header.move_silently);
    ui->stat_find_traps->setValue(cre_header.find_traps);
    ui->stat_detect_illusions->setValue(cre_header.detect_illusion);
    ui->stat_set_traps->setValue(cre_header.set_traps);
    ui->stat_pickpocket->setValue(cre_header.pick_pockets);
    ui->stat_open_locks->setValue(cre_header.open_locks);
}

void SaveGameWidget::populate_character_data( const GamCharacterData& char_data ) const
{
    ui->stat_strongest_xp->setValue( static_cast<i32>(char_data.character_stats.most_powerful_vanquished_xp) );
    if ( const auto strongest_killed = tlk->at( char_data.character_stats.most_powerful_vanquished_name))
        ui->label_strongest_name->setPlainText( QString::fromStdString( strongest_killed->std_string() ));
}

void SaveGameWidget::populate_party_metrics() const
{
    if (const auto gold = gam->header().party_gold; in_range<i32>(gold))
        ui->stat_gold->setValue( static_cast<i32>(gold) );
    else
        qWarning() << "Gold outside of range of valid values:" << gold;

    if (const auto reputation = gam->header().party_reputation; in_range<i32>(reputation))
        ui->stat_reputation->setValue( static_cast<i32>(reputation / 10) );
    else
        qWarning() << "Reputation outside of range of valid values:" << reputation;
}

#pragma endregion
