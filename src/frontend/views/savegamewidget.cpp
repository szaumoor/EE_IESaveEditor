#include "savegamewidget.h"
#include "ui_savegamewidget.h"
#include "css.h"

#include "../../backend/tlk_file.h"

#include <QShortcut>

using std::in_range;

SaveGameWidget::SaveGameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::SaveGameWidget), dlg(this)
{
    ui->setupUi(this);

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
        //complete_ui( in_range<u32>(slider_value) ? static_cast<u32>(slider_value) : 0u );
        complete_ui( slider_value );
    } );

    auto slider_policy = ui->slider_pmember->sizePolicy();
    slider_policy.setRetainSizeWhenHidden( true );
    ui->slider_pmember->setSizePolicy(slider_policy);

    ui->globals_table->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    ui->locals_table->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    ui->tabWidget->setStyleSheet(css::kTabWidget);
    ui->slider_pmember->setStyleSheet(css::kPartyMemberSlider);
}

SaveGameWidget::~SaveGameWidget()
{
    delete ui;
}

void SaveGameWidget::inject_data( const GamFile& file, const TlkFile& tlk_file )
{
    gam.emplace( file );

    if (!gam)
    {
        dlg.error(tr("Error loading data into the UI"));
        return;
    }

    tlk.emplace( tlk_file );

    if (!tlk)
    {
        dlg.error(tr("Error loading TLK file"));
        return;
    }
    complete_ui(0);
}

bool SaveGameWidget::complete_ui(const int index)
{
    if ( !in_range<u32>(index) )
        return false;

    const auto uindex = static_cast<u32>(index);

    const auto& members = gam->party_members();
    const auto& cre_members = gam->party_members_cre();

    if (members.size() == 1)
        ui->slider_pmember->hide();
    else
    {
        ui->slider_pmember->setRange(0, static_cast<int>(members.size()) - 1);
        ui->slider_pmember->setVisible(true);
    }

    setEnabled( true );

    const auto& party_member= members[uindex];
    const CreFile& cre_party_member = cre_members[uindex];

    const auto& cre_header = cre_party_member.header();

    const auto [strength,
        strength_bonus,
        intelligence,
        wisdom,
        dexterity,
        constitution,
        charisma
    ] = cre_party_member.header().stats;

    ui->stat_strength->setValue( strength );
    ui->stat_str_extra->setValue( strength_bonus );
    ui->stat_dexterity->setValue( dexterity );
    ui->stat_constitution->setValue( constitution );
    ui->stat_intelligence->setValue( intelligence );
    ui->stat_wisdom->setValue( wisdom );
    ui->stat_charisma->setValue( charisma );

    const auto [ac_natural,
        ac_effective,
        ac_crushing,
        ac_missile,
        ac_piercing,
        ac_slashing
    ] = cre_party_member.header().armor_class;

    ui->ac_base->setValue( ac_effective );
    ui->ac_effective->setValue( ac_effective );
    ui->ac_piercing->setValue( ac_piercing );
    ui->ac_crush->setValue( ac_crushing );
    ui->ac_slashing->setValue( ac_slashing );
    ui->ac_missile->setValue( ac_missile );


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
    ] = cre_party_member.header().resistances;

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

    const auto [saving_throw_vs_death,
        saving_throw_vs_wands,
        saving_throw_vs_poly,
        saving_throw_vs_breath,
        saving_throw_vs_spell
    ] = cre_party_member.header().saving_throws;

    ui->save_death->setValue( saving_throw_vs_death);
    ui->save_wand->setValue( saving_throw_vs_wands);
    ui->save_poly->setValue(saving_throw_vs_poly);
    ui->save_breath->setValue(saving_throw_vs_breath);
    ui->save_spell->setValue(saving_throw_vs_spell);

    ui->name_label->setPlainText( QString::fromStdString( party_member.name.to_string() ) );

    ui->stat_hide_shadows->setValue(cre_party_member.header().hide_in_shadows);
    ui->stat_move_silently->setValue(cre_party_member.header().move_silently);
    ui->stat_find_traps->setValue(cre_party_member.header().find_traps);
    ui->stat_detect_illusions->setValue(cre_party_member.header().detect_illusion);
    ui->stat_set_traps->setValue(cre_party_member.header().set_traps);
    ui->stat_pickpocket->setValue(cre_party_member.header().pick_pockets);
    ui->stat_open_locks->setValue(cre_party_member.header().open_locks);

    ui->stat_first_level->setValue(cre_party_member.header().class_levels[0]);
    ui->stat_second_level->setValue(cre_party_member.header().class_levels[1]);
    ui->stat_third_level->setValue(cre_party_member.header().class_levels[2]);

    ui->stat_lore->setValue(cre_party_member.header().lore);
    ui->stat_intoxication->setValue(cre_party_member.header().intoxication);
    ui->stat_morale->setValue(cre_party_member.header().morale);
    ui->stat_morale_break->setValue(cre_party_member.header().morale_break);
    ui->stat_morale_rec->setValue(cre_party_member.header().morale_recovery_time);

    ui->stat_fatigue->setValue(cre_party_member.header().fatigue);

    if (const auto gold = gam->header().party_gold; in_range<i32>(gold))
        ui->stat_gold->setValue( static_cast<i32>(gold) );
    else
        qWarning() << "Gold outside of range of valid values:" << gold;

    if (const auto reputation = gam->header().party_reputation; in_range<i32>(reputation))
        ui->stat_reputation->setValue( static_cast<i32>(reputation) );
    else
        qWarning() << "Reputation outside of range of valid values:" << reputation;

    if (const auto stat_xp = cre_header.xp_gained_kills; in_range<i32>(stat_xp))
        ui->stat_xp->setValue( static_cast<i32>(stat_xp) );
    else
        qWarning() << "Stat XP outside of range of valid values:" << stat_xp;

    if (const auto stat_xp_for_kill = cre_header.xp_creature; in_range<i32>(stat_xp_for_kill))
        ui->stat_xp_for_kill->setValue( static_cast<i32>(stat_xp_for_kill) );
    else
        qWarning() << "XP for kill outside of range of valid values:" << stat_xp_for_kill;

    if (const auto greater_vanquished = party_member.character_stats.most_powerful_vanquished_xp; in_range<i32>(greater_vanquished))
        ui->stat_strongest_xp->setValue( static_cast<i32>(greater_vanquished) );
    else
        qWarning() << "XP of most powerful vanquished outside of range of valid values:" << greater_vanquished;


    ui->stat_strongest_xp->setValue( static_cast<i32>(party_member.character_stats.most_powerful_vanquished_xp) );

    ui->stat_base_thac0->setValue( cre_party_member.header().thac0 );


    if ( const auto strongest_killed = tlk->at( party_member.character_stats.most_powerful_vanquished_name))
        ui->label_strongest_name->setPlainText( QString::fromStdString( strongest_killed->std_string() ));

    ui->stat_cur_hp->setValue( cre_party_member.header().current_hit_points );
    ui->stat_max_hp->setValue( cre_party_member.header().max_hit_points );

    m_global_model->set_variables( gam->globals() );
    m_local_model->set_variables( cre_party_member.locals() );

    return true;
}
